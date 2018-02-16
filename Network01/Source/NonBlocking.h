#pragma once
#include "Protocol.h"

class NonBlocking : public Protocol {
public:
	NonBlocking(sf::TcpSocket* _socket);
	~NonBlocking();
};
