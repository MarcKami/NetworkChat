#include "Threading.h"

Threading::Threading(sf::TcpSocket* _socket) {
	socket = _socket;
}

Threading::~Threading() {

}

void Threading::Run(void) {

	string sendText;
	size_t received = 0;

	vector<pair<string, string>> aMensajes;
	pair<string, string> message;
	string messageSend;
	Receptor_Threading r(socket, &aMensajes);
	sf::Packet myPacket;
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


	sf::Text text(mensaje, font, 14);
	text.setFillColor(sf::Color(0, 160, 0));
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);
#pragma endregion

#pragma region InteractionLoop
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
						messageSend = mensaje;
						myPacket << nick << messageSend;
						socket->send(myPacket);
						window.close();
					}
					else {
						//SEND
						messageSend = mensaje;
						myPacket << nick << messageSend;
						sf::Socket::Status status = socket->send(myPacket);
						if (status != sf::Socket::Done) {
							cout << "Ha fallado el envio de datos\n";
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
			chatting += aMensajes[i].second;
			chattingText.setPosition(sf::Vector2f(0, 20 * (float)i));
			chattingText.setString(chatting);
			if (aMensajes[i].first == nick) {
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

	socket->disconnect();

	t.join();
}