#include "Protocol.h"

using namespace std;
using namespace utils;

class Receptor {
public:
	sf::TcpSocket* sock;
	vector<pair<string, originText>>* aMsj;
	pair<string, originText> message;
	char receivedText[MAX_LENGTH];
	size_t receivedLength;

	Receptor(){
	}
	Receptor(sf::TcpSocket* sock, vector<pair<string, originText>>* aMsj) : sock(sock),
		aMsj(aMsj) {
	}

	void operator() () {
		bool end = false;
		while (!end) {
			sf::Socket::Status status = sock->receive(receivedText, MAX_LENGTH, receivedLength);
			if (status != sf::Socket::Done) {
				//Ha fallado la recepción de datos
				end = true;
			}
			else {
				message = { receivedText, other };
				aMsj->push_back(message);
				for (int i = 0; i < receivedLength; i++)
					receivedText[i] = ' ';
				if (aMsj->size() > 25) {
					aMsj->erase(aMsj->begin(), aMsj->begin() + 1);
				}
			}
		}
	}
};

class Threading : public Protocol {
public:
	Threading() = default;
	Threading(sf::TcpSocket* socket, vector<pair<string, originText>>* aMensajes);
	~Threading();

	void Enter();
	void Update();
	void Exit();

	Receptor r;
private:
};
