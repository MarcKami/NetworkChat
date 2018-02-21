#pragma once
#include "Protocol.h"

class SocketSelector : public Protocol {
public:
	SocketSelector(vector<sf::TcpSocket*> _sockets);
	~SocketSelector();

	void Protocol::Run();

private:
	vector<sf::TcpSocket*> sockets;
};
