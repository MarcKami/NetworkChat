#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <thread>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PORT 5000
#define MAX_MENSAJES 30
#define MAX_LENGTH 100

#define MINE_COLOR sf::Color(0, 160, 0)
#define OTHER_COLOR sf::Color(0, 160, 160)

enum originText { mine, other };

using namespace std;

class Receptor {
public:
	sf::TcpSocket* sock;
	vector<pair<string, originText>>* aMsj;
	pair<string, originText> message;
	char receivedText[MAX_LENGTH];
	size_t receivedLength;

	Receptor(sf::TcpSocket* sock, vector<pair<string, originText>>* aMsj) :	sock(sock),
																			aMsj(aMsj){
	}

	void operator() () {
		bool end = false;
		while (!end) {
			sf::Socket::Status status = sock->receive(receivedText, MAX_LENGTH, receivedLength);
			if (status != sf::Socket::Done) {
				//Ha fallado la recepción de datos
				end = true;
			}
			else {
				message = { receivedText, other };
				aMsj->push_back(message);
				for (int i = 0; i < receivedLength; i++)
					receivedText[i] = ' ';
				if (aMsj->size() > 25) {
					aMsj->erase(aMsj->begin(), aMsj->begin() + 1);
				}
			}
		}
	}
};

int main() {
#pragma region Connection
	//ESTABLECER CONEXION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType, mode, prot;
	string sendText;
	size_t received;
	string text1 = "Connected to: ";

	cout << "Enter (s) for Server, Enter (c) for Client: ";
	cin >> connectionType;

	if (connectionType == 's') {
		cout << "\nPROTOCOL\n- (1) for Threading\n- (2) for NonBlocking\n- (3) for SocketSelector\n\nYour selection: ";
		cin >> prot;
		int type = (int)prot;

		sf::TcpListener listener;
		listener.listen(PORT);
		listener.accept(socket);
		text1 += "Server";
		mode = 's';
		listener.close();

		sf::Socket::Status status = socket.send(&prot, sizeof(char));
		if (status != sf::Socket::Done) {
			//Ha fallado el envío de datos
		}
	}
	else if (connectionType == 'c') {
		socket.connect(ip, PORT);
		text1 += "Client";
		mode = 'r';

		char* protocolType = "";
		size_t protocolLength;
		sf::Socket::Status status = socket.receive(protocolType, MAX_LENGTH, protocolLength);
		if (status != sf::Socket::Done) {
			//Ha fallado la recepción de datos
		}
		else {
			int type = (int)protocolType;
			switch (type) {
			case 1: //Threading
				//myProtocol = Threading;
				break;
			case 2: //NonBlocking
				//myProtocol = NonBlocking;
				break;
			case 3: //SocketSelector
				//myProtocol = SocketSelector;
				break;
			default:
				//Error en el tipo de protocolo
				break;
			}
		}
	}
#pragma endregion

	vector<pair<string, originText>> aMensajes;
	pair<string, originText> message;
	Receptor r(&socket, &aMensajes);
	thread t(r);

#pragma region ScreenDisplay
	sf::Vector2i screenDimensions(SCREEN_WIDTH, SCREEN_HEIGHT);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Chat");

	sf::Font font;
	if (!font.loadFromFile("courbd.ttf")) {
		std::cout << "Can't load the font file" << std::endl;
	}

	sf::String mensaje = " > ";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	//chattingText.setStyle(sf::Text::Bold);


	sf::Text text(mensaje, font, 14);
	text.setFillColor(sf::Color(0, 160, 0));
	//text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);
#pragma endregion

#pragma region InteractionLoop
	/*switch (myProtocol) {
	case Threading:
		break;
	case NonBlocking:
		break;
	case SocketSelector:
		break;
	default:
		break;
	}*/
	while (window.isOpen()) {
		sf::Event evento;
		while (window.pollEvent(evento)) {
			switch (evento.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape)
					window.close();
				else if (evento.key.code == sf::Keyboard::Return) {
					if (mensaje == " > exit") {
						sendText = "The other user has disconnected";
						socket.send(sendText.c_str(), sendText.length());
						window.close();
					}
					else {
						message = { mensaje, mine };
						aMensajes.push_back(message);
						if (aMensajes.size() > 25) {
							aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
						}
						//SEND
						sendText = mensaje;
						sf::Socket::Status status = socket.send(sendText.c_str(), sendText.length());
						if (status != sf::Socket::Done) {
							//Ha fallado el envío de datos
						}
						mensaje = " > ";
					}
				}
				break;
			case sf::Event::TextEntered:
				if (evento.text.unicode >= 32 && evento.text.unicode <= 126)
					mensaje += (char)evento.text.unicode;
				else if (evento.text.unicode == 8 && mensaje.getSize() > 0)
					mensaje.erase(mensaje.getSize() - 1, mensaje.getSize());
				break;
			}
		}
		window.draw(separator);
#pragma endregion

#pragma region DrawMessages
		for (size_t i = 0; i < aMensajes.size(); i++) {
			string chatting = aMensajes[i].first;
			chattingText.setPosition(sf::Vector2f(0, 20 * i));
			chattingText.setString(chatting);
			if (aMensajes[i].second == mine) {
				chattingText.setFillColor(MINE_COLOR);
			}
			else {
				chattingText.setFillColor(OTHER_COLOR);
			}
			window.draw(chattingText);
		}
		string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		window.draw(text);
#pragma endregion

		window.display();
		window.clear();
	}
}
