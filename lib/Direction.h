#pragma once
#include <string>
#include <SFML\Network.hpp>

struct Direction {

	Direction(std::string ip, unsigned short port) :	ip(ip),
														port(port){
	}
	Direction() = default;

	std::string ip;
	unsigned short port;
};