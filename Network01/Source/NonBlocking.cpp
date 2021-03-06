#include "NonBlocking.h"

NonBlocking::NonBlocking(sf::TcpSocket* _socket) {
	socket = _socket;
	socket->setBlocking(false);
}

NonBlocking::~NonBlocking() {

}

void NonBlocking::Run(void) {

	string sendText, receiveText;

	vector<pair<string, originText>> aMensajes;
	pair<string, originText> messageSended, messageReceived;

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
					sf::Packet toSend;
					if (mensaje == " > exit") {
						sendText = "The other user has disconnected";
						toSend << sendText;
						socket->send(toSend);
						window.close();
					}
					else {
						messageSended = { mensaje, mine };
						aMensajes.push_back(messageSended);
						if (aMensajes.size() > 25) {
							aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
						}
						//SEND
						sendText = mensaje;
						toSend << sendText;
						sf::Socket::Status status = socket->send(toSend);
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

		sf::Packet toReceive;
		sf::Socket::Status status = socket->receive(toReceive);
		if (status == sf::Socket::Done) {
			toReceive >> receiveText;
			messageReceived = { receiveText, other };
			aMensajes.push_back(messageReceived);
			if (aMensajes.size() > 25) {
				aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
			}
		}
		else if (status == sf::Socket::Disconnected) {
			break;
		}

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


	socket->disconnect();

}