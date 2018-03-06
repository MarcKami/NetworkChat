#pragma once
#include <string>
#include <SFML\Network.hpp>

struct Direction {

	Direction(sf::IpAddress ip, unsigned short port) :	ip(ip),
														PORT(port){
	}

	sf::IpAddress ip;
	unsigned short PORT;
};