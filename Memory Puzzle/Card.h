#pragma once
#include <iostream>
#include <string>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

enum class CardValue { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum class CardSuite { SPADES = 1, DIAMONDS, HEARTS, CLUBS };

class Card
{
public:
	Card() = default;
	Card(float x, float y, int c, int s);

	void flipCard();
	bool intersects(const sf::Vector2f&);
	const bool flippedUp();
	int getCardValue();

	void update();
	void render(sf::RenderTarget&);
private:
	//Variables
	sf::Sprite faceUpCardSprite;
	sf::Sprite faceDownCardSprite;
	sf::Texture faceUpCardTexture;
	sf::Texture faceDownCardTexture;

	std::string faceUpImageFileName;
	static std::string faceDownImageFileName;

	CardSuite suite;
	CardValue value;

	float posX;
	float posY;

	bool flippedDown;

	//Helpers
	std::string getCardValName();
	std::string getCardSuiteName();

	//Functions
	void initVariables();
	void initCardFileNames();
	void initCard();
};

