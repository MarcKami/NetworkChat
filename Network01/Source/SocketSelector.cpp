#include "SocketSelector.h"

SocketSelector::SocketSelector(vector<sf::TcpSocket*> _sockets) {
	sockets = _sockets;
}

SocketSelector::~SocketSelector() {

}

void SocketSelector::Run(void) {

	string sendText;
	size_t received = 0;

	vector<pair<string, originText>> aMensajes;
	pair<string, originText> message;
	Receptor_Selection r(sockets, &aMensajes);
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
						sendText = "The other user has disconnected";
						for each (sf::TcpSocket* s in sockets) {
							s->send(sendText.c_str(), sendText.length());
						}
						window.close();
					}
					else {
						message = { mensaje, mine };
						mu.lock();
						aMensajes.push_back(message);
						if (aMensajes.size() > 25) {
							aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
						}
						mu.unlock();
						//SEND
						sendText = mensaje;
						for each (sf::TcpSocket* s in sockets) {
							sf::Socket::Status status = s->send(sendText.c_str(), sendText.length());
							if (status == sf::Socket::Error) {
								cout << "Ha fallado el envio de datos\n";
							}
							else if (status == sf::Socket::Disconnected) {
								cout << "Ha fallado el envio de datos\n";
								s->disconnect();
							}
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
			chattingText.setPosition(sf::Vector2f(0, 20 * (float)i));
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

	for each (sf::TcpSocket* s in sockets) {
		s->disconnect();
	}

	t.join();
}