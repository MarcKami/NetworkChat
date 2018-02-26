#pragma once
#include <SFML\Network.hpp>
#include <iostream>
#include <mutex>
#include "Utils.hpp"

using namespace utils;
using namespace std;

struct Receptor_Selection {
public:
	vector<pair<string, string>>* aMsj;

	Receptor_Selection(vector<pair<string, string>>* aMsj) : aMsj(aMsj){
	}

	void operator() () {
		sf::TcpSocket incoming;
		sf::TcpListener dispatcher;
		vector<sf::TcpSocket*> sock;
		sf::SocketSelector selector;
		string nick = "";
		string receivedText = "";
		pair<string, string> message;
		sf::Packet myPack;

		//sf::Socket::Status status = dispatcher.listen(PORT); 
		if (dispatcher.listen(PORT) != sf::Socket::Done) {
			cout << "No se puede vincular al puerto 5000\n";
		}
		selector.add(dispatcher);
		while (selector.wait()) {
			if (selector.isReady(dispatcher)) {
				sf::TcpSocket* socket = new sf::TcpSocket();
				if (dispatcher.accept(*socket) == sf::Socket::Done) {
					sock.push_back(socket);
					selector.add(*socket);
				}
				else {
					delete socket;
				}
			}
			else {
				for (int i = 0; i < sock.size(); i++) {
					if (selector.isReady(*sock[i])) {
						if (sock[i]->receive(myPack) == sf::Socket::Status::Done) {
							myPack >> nick >> receivedText;
							if (receivedText == " > exit") {
								selector.remove(*sock[i]);
								sock[i]->disconnect();
								sock.erase(sock.begin() + i);
								for (int j = 0; j < sock.size(); j++) {
									myPack << nick << " se ha desconectado";
									sock[j]->send(myPack);
								}
								break;
							}
							else {
								for (int j = 0; j < sock.size(); j++) {
									sock[j]->send(myPack);
								}
							}
						}
						else {
							selector.remove(*sock[i]);
							sock[i]->disconnect();
							sock.erase(sock.begin() + i);
							for (int j = 0; j < sock.size(); j++) {
								myPack << nick << " se ha desconectado";
								sock[j]->send(myPack);
							}
							break;
						}
						break;
					}
				}
			}
		}
	}
};