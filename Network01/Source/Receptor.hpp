#pragma once
#include <SFML\Network.hpp>
#include <iostream>
#include <mutex>
#include "Utils.hpp"

using namespace utils;
using namespace std;

struct Receptor_Threading {
public:
	sf::TcpSocket* sock;
	vector<pair<string, string>>* aMsj;
	pair<string, string> message;
	sf::Packet myPacket;
	size_t receivedLength;

	Receptor_Threading(sf::TcpSocket* sock, vector<pair<string, string>>* aMsj) :	sock(sock),
																					aMsj(aMsj) {
	}

	void operator() () {
		bool end = false;
		while (!end) {
			sf::Socket::Status status = sock->receive(myPacket);
			if (status != sf::Socket::Done) {
				cout << "Ha fallado la recepcion de datos\n";
				end = true;
			}
			else {
				myPacket >> message.first >> message.second;
				mu.lock();
				aMsj->push_back(message);
				if (aMsj->size() > 25) {
					aMsj->erase(aMsj->begin(), aMsj->begin() + 1);
				}
				mu.unlock();
			}
		}
	}
};


struct Receptor_Selection {
public:
	vector<sf::TcpSocket*> sock;
	sf::SocketSelector selector;
	vector<pair<string, originText>>* aMsj;
	pair<string, originText> message;
	char receivedText[MAX_LENGTH];
	size_t receivedLength;

	Receptor_Selection(vector<sf::TcpSocket*> sock, vector<pair<string, originText>>* aMsj) : sock(sock),
		aMsj(aMsj) {
		for each (sf::TcpSocket* s in sock)
		{
			selector.add(*s);
		}
	}

	void operator() () {
		bool end = false;
		for (int i = 0; i < MAX_LENGTH; i++)
			receivedText[i] = ' ';
		while (!end) {
			if(selector.wait()) {
				for each (sf::TcpSocket* s in sock)
				{
					sf::Socket::Status status = s->receive(receivedText, MAX_LENGTH, receivedLength);
					if (status != sf::Socket::Done) {
						if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
							end = true;
						cout << "No es este socket\n";
						continue;
					}
					else{
						message = { receivedText, other };
						aMsj->push_back(message);
						for (int i = 0; i < MAX_LENGTH; i++)
							receivedText[i] = ' ';
						if (aMsj->size() > 25) {
							aMsj->erase(aMsj->begin(), aMsj->begin() + 1);
						}
					}
				}
			}
		}
	}
};