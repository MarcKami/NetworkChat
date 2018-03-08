#include <SFML\Network.hpp>
#include <iostream>
#include "Direction.h"
#include "Utils.h"

void main() {
	Direction dir[MAX_PLAYERS - 1];
	vector<sf::TcpSocket*> sock;
	sf::TcpSocket serverSock;
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpListener listener;

#pragma region Connection
	//Connect to server
	if (serverSock.connect(ip, PORT) != sf::Socket::Done)
		cout << "No se puede conectar al servidor" << endl;
	else {
		sf::Packet peers;
		cout << "Esperando Peers" << endl;
		if(serverSock.receive(peers) != sf::Socket::Done)
			cout << "No se recibieron los otros peers" << endl;
		else {
			unsigned short myPort = serverSock.getLocalPort();
			serverSock.disconnect();
			cout << "Peers recibidos" << endl;
			int players;
			peers >> players;
			for (int i = 0; i < players; i++) {
				sf::TcpSocket* auxSock = new sf::TcpSocket();
				peers >> dir[i].ip >> dir[i].port;
				cout << "Socket " << i << ": IP - " << dir[i].ip << " PORT - " << dir[i].port << endl;
				if (auxSock->connect(ip, dir[i].port) != sf::Socket::Done) {
					cout << "Imposible conectar al peer: " << i << endl;
				}
				else {
					cout << "Conexion con exito al peer: " << i << endl;
					sock.push_back(auxSock);
				}
			}
			if (listener.listen(myPort) != sf::Socket::Done) {
				cout << "No se puede vincular al puerto 5000" << endl;
			}
			for (int i = 0; i < MAX_PLAYERS - 1 - players; i++) {
				sf::TcpSocket* auxSock = new sf::TcpSocket();
				if (listener.accept(*auxSock) == sf::Socket::Done)
					sock.push_back(auxSock);
			}
			listener.close();
		}
	}

	for each (sf::TcpSocket* s in sock) {
		cout << "Socket: IP - " << s->getRemoteAddress().toString() << " PORT - " << s->getRemotePort() << endl;
	}

	int xwfw;
	std::cin >> xwfw;
#pragma endregion

	for each (sf::TcpSocket* s in sock) {
		s->disconnect();
	}
}