#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include "Utils.hpp"

class Protocol {
public:
	Protocol();
	~Protocol();

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

private:

};
