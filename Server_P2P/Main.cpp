#include <SFML\Network.hpp>
#include <iostream>
#include "Direction.h"
#include "Utils.h"

void RecieveClients(sf::TcpListener* listener, vector<Direction>* aPeers, sf::TcpSocket* sock) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		listener->accept(sock[i]);
		Direction d(sock[i].getRemoteAddress().toString(), sock[i].getRemotePort());
		cout << "Socket " << i << ": IP - " << d.ip << " PORT - " << d.port << endl;
		aPeers->push_back(d);
	}
}

void ConnectClients(vector<Direction> aPeers, sf::TcpSocket* sock) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		sf::Packet pack;
		int idx = 0;
		pack << MAX_PLAYERS - 1;
		for (int j = 0; j < MAX_PLAYERS; j++) {
			if (j != i)
				pack << aPeers[j].ip << aPeers[j].port;
		}
		sock[i].send(pack);
	}
}

void main() {
	//ESTABLECER CONEXION
	vector<Direction> aPeers;
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpListener listener;
	sf::TcpSocket sock[MAX_PLAYERS];
	
	if (listener.listen(PORT) != sf::Socket::Done) {
		cout << "No se puede vincular al puerto 5000\n";
	}

	//Connect clients
	RecieveClients(&listener, &aPeers, sock);
	ConnectClients(aPeers, sock);

	//Disconnect server
	//listener.close();
	for (int i = 0; i < MAX_PLAYERS; i++)
		sock[i].disconnect();
	delete[] sock;
}