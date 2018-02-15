#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "Utils.hpp"

using namespace utils;
using namespace std;

class Protocol {
public:
	Protocol();
	~Protocol();

	virtual void Run();
private:

protected:
	sf::TcpSocket* socket;
	vector<pair<string, originText>>* aMensajes;
};
