#include <SFML\Network.hpp>
#include <iostream>
#include "Direction.h"
#include "Utils.h"

using namespace std;

void main() {
#pragma region Connection
	//ESTABLECER CONEXION
	vector<Direction> aPeers;
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpListener listener;
	
	if (listener.listen(PORT) != sf::Socket::Done) {
		cout << "No se puede vincular al puerto 5000\n";
	}

	for (int i = 0; i < MAX_PLAYERS; i++) {
		sf::TcpSocket sock;
		listener.accept(sock);
		Direction d(sock.getRemoteAddress(), sock.getRemotePort());
		aPeers.push_back(d);
		//QUE FALTA??
	}
}