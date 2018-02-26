#pragma once
#include <SFML\Network.hpp>
#include <iostream>
#include <mutex>
#include "Utils.hpp"

using namespace utils;
using namespace std;

struct Receptor_Selection {
public:
	vector<sf::TcpSocket*> sock;
	sf::SocketSelector selector;
	vector<pair<string, string>>* aMsj;
	pair<string, string> message;
	string nick;
	string receivedText;

	Receptor_Selection(vector<sf::TcpSocket*> sock, vector<pair<string, string>>* aMsj) :	sock(sock),
																							aMsj(aMsj) {
		for each (sf::TcpSocket* s in sock) {
			selector.add(*s);
		}
	}

	void operator() () {
		bool end = false;
		while (!end) {
			if(selector.wait()) {
				for each (sf::TcpSocket* s in sock) {
					sf::Packet receivedPacket;
					sf::Socket::Status status = s->receive(receivedPacket);
					if (status != sf::Socket::Done) {
						if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
							end = true;
						cout << "No es este socket\n";
						continue;
					}
					else{
						sendData = receivedPacket;
						receivedPacket >> nick >> receivedText;
						message = { nick, receivedText };
						mu.lock();
						aMsj->push_back(message);
						if (aMsj->size() > 25) {
							aMsj->erase(aMsj->begin(), aMsj->begin() + 1);
						}
						mu.unlock();
					}
				}
			}
		}
	}
};