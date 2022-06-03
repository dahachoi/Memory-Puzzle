#pragma once
#include <string>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Player{
private:
	std::string name;
	int points;
	

	//Initialization Functions

public:
	Player();

	//Functions
	int getPoints();
	std::string getName();
	void setName(const std::string&);
	void incrementPoint(const int&);

	//Initialization Functions
	void initVariables();
};

