#include "Protocol.h"

struct Receptor {
public:
	sf::TcpSocket* sock;
	vector<pair<string, originText>>* aMsj;
	pair<string, originText> message;
	char receivedText[MAX_LENGTH];
	size_t receivedLength;

	Receptor(sf::TcpSocket* sock, vector<pair<string, originText>>* aMsj) : sock(sock),
		aMsj(aMsj) {
	}

	void operator() () {
		bool end = false;
		for (int i = 0; i < MAX_LENGTH; i++)
			receivedText[i] = ' ';
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
	Threading(sf::TcpSocket* _socket);
	~Threading();

private:
};
