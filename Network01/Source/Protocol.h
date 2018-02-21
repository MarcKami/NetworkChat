#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "Receptor.hpp"

class Protocol {
public:
	Protocol();
	~Protocol();

	virtual void Run(void) = 0;
};
