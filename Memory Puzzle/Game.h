#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "Card.h"
#include "Player.h"

class Game
{
public:
	Game() = default;
	Game(const std::string&, const std::string&);
	~Game();

	const bool running() const;

	void update();
	void render();
private:
	//SFML
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	bool endGame;
	sf::Event ev;

	const int windowX = 1200;
	const int windowY = 700;

	sf::Font font;
	sf::Text titleText;
	sf::Text p1Text;
	sf::Text p2Text;
	sf::Text timerText;
	sf::Text endGameText;
	sf::Text pointDisplayText;

	sf::Color pointDisplayColor;

	sf::Clock clock;
	sf::Time elapsed;

	int timerMax;

	//Game logic
	const int maxCardsFlipped = 2;
	int cardsFlipped;
	std::vector<Card*> faceUpCardPair;

	//Background
	sf::Sprite guiBackGround;
	sf::Texture guiBackGroundTexture;

	//Objects
	std::vector<Card*> playingCards;
	std::vector<std::pair<int, int>> pairValSuite;

	int maxCards;
	float xGapOfCards;
	float yGapOfCards;

	Player player1;
	Player player2;
	Player* playerTurn;
	bool playerOnesTurn;
	int pointGain;
	int pointMultiplier;


	//Initialization functions
	void initWindow();
	void initVariables();
	void initPlayers(const std::string&, const std::string&);
	void initBackground();
	void initFont();
	void initText();

	//Functions
	void spawnCards();
	void randomizeCards();
	void pollEvents();
	void setPlayerNames(const std::string&, const std::string&);
	void switchPlayerTurn();
	

	//render
	void renderCards();
	void renderGui();
	void renderPointDisplay();
	void renderPD();

	//update	
	void updateCards();
	void updateGui();
	void updateTimers();
	void updateMouse();
	void updatePoints();
	void renderGameOver();


};

