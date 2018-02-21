#pragma once

namespace utils {

	enum originText { mine, other };
	static std::mutex mu;

	#define SCREEN_WIDTH 800
	#define SCREEN_HEIGHT 600

	#define PORT 5000
	#define MAX_MENSAJES 30
	#define MAX_LENGTH 100

	#define MINE_COLOR sf::Color(0, 160, 0)
	#define OTHER_COLOR sf::Color(0, 160, 160)
}


//For future works
//struct Info
//{
//	sf::Int32 num;
//	std::string str;
//};
//
//sf::Packet& operator <<(sf::Packet& _packet, const Info& _struct)
//{
//	return _packet << _struct.num << _struct.str;
//}
//
//sf::Packet& operator>> (sf::Packet& _packet, Info& _struct)
//{
//	return _packet >> _struct.num >> _struct.str;
//}