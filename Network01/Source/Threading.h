#pragma once
#include "Protocol.h"

class Threading : public Protocol {
public:
	Threading(sf::TcpSocket* _socket);
	~Threading();

	void Protocol::Run();

private:
	sf::TcpSocket* socket;
};
