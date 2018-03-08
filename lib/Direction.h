#pragma once
#include <string>
#include <SFML\Network.hpp>

struct Direction {

	Direction(std::string nick, std::string ip, unsigned short port) :	nick(nick),
																		ip(ip),
																		port(port){
	}
	Direction() = default;

	std::string nick;
	std::string ip;
	unsigned short port;
};