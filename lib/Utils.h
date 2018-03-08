#pragma once
#include <mutex>

using namespace std;

namespace utils {

	static std::mutex mu;
	static std::string nick;

	static bool end;

	#define SCREEN_WIDTH 800
	#define SCREEN_HEIGHT 600

	#define PORT 5000
	#define MAX_MENSAJES 30
	#define MAX_LENGTH 100
	#define MAX_PLAYERS 4

	#define MINE_COLOR sf::Color(0, 160, 0)
	#define COLOR_0 sf::Color(0, 160, 160)
	#define COLOR_1 sf::Color(160, 0, 0)
	#define COLOR_2 sf::Color(0, 0, 160)
}