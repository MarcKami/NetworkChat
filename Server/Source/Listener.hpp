#pragma once
#include <SFML\Network.hpp>
#include <iostream>
#include <mutex>
#include "Utils.hpp"

using namespace utils;
using namespace std;

struct Listen_Server {
public:
	vector<sf::TcpSocket*> sock;
	int users = 0;
	bool end = false;

	Listen_Server(vector<sf::TcpSocket*> sock) : sock(sock){
	}

	void CloseListener() {
		end = true;
	}

	void operator() () {
		sf::TcpSocket incoming;
		sf::TcpListener dispatcher;
		while (!end) {
			sf::Socket::Status status = dispatcher.listen(PORT);
			if (status != sf::Socket::Done) {
				cout << "No se puede vincular al puerto 5000\n";
				end = true;
			}
			while (users < MAX_USERS) {
				if (dispatcher.accept(incoming) != sf::Socket::Done) {
					cout << "Error al aceptar conexión\n";
					end = true;
				}
				else {
					users++;
					mu.lock();
					sock.push_back(&incoming);
					mu.unlock();
				}
			}
		}
		dispatcher.close();
	}
};