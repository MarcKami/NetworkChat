#pragma once

namespace utils {

	enum originText { one, two, three, four };
	static std::mutex mu;
	static sf::Packet sendData;

	#define SCREEN_WIDTH 800
	#define SCREEN_HEIGHT 600

	#define PORT 5000
	#define MAX_USERS 4
	#define MAX_MENSAJES 30
	#define MAX_LENGTH 100

	#define ONE_COLOR sf::Color(0, 160, 0)
	#define TWO_COLOR sf::Color(0, 160, 160)
	#define THREE_COLOR sf::Color(160, 0, 0)
	#define FOUR_COLOR sf::Color(160, 0, 160)
}


//For future works
struct Info
{
	std::string nick, str;
};

sf::Packet& operator<< (sf::Packet& _packet, const Info& _struct)
{
	return _packet << _struct.nick << _struct.str;
}

sf::Packet& operator>> (sf::Packet& _packet, Info& _struct)
{
	return _packet >> _struct.nick >> _struct.str;
}