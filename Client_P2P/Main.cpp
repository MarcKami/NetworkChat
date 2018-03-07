#include <SFML\Network.hpp>
#include <iostream>
#include "Direction.h"
#include "Utils.h"

void main() {
	Direction dir[MAX_PLAYERS - 1];
	sf::TcpSocket sock[MAX_PLAYERS - 1];
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

#pragma region Connection
	//Connect to server
	if (sock[0].connect(ip, PORT) != sf::Socket::Done)
		cout << "No se puede conectar al servidor" << endl;
	else {
		sf::Packet peers;
		cout << "Esperando Peers" << endl;
		if(sock[0].receive(peers) != sf::Socket::Done)
			cout << "No se recibieron los otros peers" << endl;
		else {
			sock[0].disconnect();
			cout << "Peers recibidos" << endl;
			int size;
			peers >> size;
			for (int i = 0; i < size; i++) {
				peers >> dir[i].ip >> dir[i].port;
				cout << "Socket " << i << ": IP - " << dir[i].ip << " PORT - " << dir[i].port << endl;
				if (sock[i].connect(dir[i].ip, dir[i].port) != sf::Socket::Done) {
					cout << "Imposible conectar al peer " << i << endl;
				}
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		cout << "Socket " << i << ": " << sock[i].getRemotePort() << endl;
	}
	int xwfw;
	cin >> xwfw;
#pragma endregion



}