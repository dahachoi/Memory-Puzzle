#include "Card.h"

using namespace std;

Card::Card(float x, float y, int v, int s)
	: posX(x), posY(y), value(static_cast<CardValue>(v)), suite(static_cast<CardSuite>(s))
{
	//cout << "constructor called!" << endl;
	//cout << "posX : " << posX << ", posY : " << posY << endl;
	//cout << "CardValue : " << int(value) << ", CardSuite : " << int(suite) << "\n\n";

	if (v < 1 || v > 13) cerr << "Card Value too big or small." << endl;
	if (s < 1 || s > 4) cerr << "Suite Value too big or small." << endl;

	initVariables();
	initCardFileNames();
	initCard();
}

void Card::initVariables() {
	flippedDown = true;
	faceUpCardSprite.setScale(0.22f, 0.22f);
	faceDownCardSprite.setScale(0.22f, 0.22f);
}

void Card::initCardFileNames() {
	faceUpImageFileName = "Game_Sprites\\\\PNG-cards-1.3\\\\";
	faceUpImageFileName += getCardValName();
	faceUpImageFileName += getCardSuiteName();
}

string Card::faceDownImageFileName = "Game_Sprites\\\\PNG-cards-1.3\\\\500x707.png";

void Card::initCard() {
	//faceUp
	if (!faceUpCardTexture.loadFromFile(faceUpImageFileName))
		cout << "failed to load image : " << faceUpImageFileName << endl;

	faceUpCardTexture.setSmooth(true);
	faceUpCardSprite.setTexture(faceUpCardTexture);
	faceUpCardSprite.setPosition(sf::Vector2f(posX, posY));
	

	//faceDown
	if (!faceDownCardTexture.loadFromFile(faceDownImageFileName))
		cout << "failed to load image : " << faceDownImageFileName << endl;

	faceDownCardTexture.setSmooth(true);
	faceDownCardSprite.setTexture(faceDownCardTexture);
	faceDownCardSprite.setPosition(sf::Vector2f(posX, posY));
	//faceDownCardSprite.setTextureRect(sf::IntRect(posX, posY, 500, 726))

	//cout << "width of face up card : " << faceUpCardSprite.getGlobalBounds().width << endl;
	//cout << "height of face up card : " << faceUpCardSprite.getGlobalBounds().height << endl;

	//cout << "width of face down card : " << faceDownCardSprite.getGlobalBounds().width << endl;
	//cout << "height of face down card : " << faceDownCardSprite.getGlobalBounds().height << endl;

}

void Card::flipCard() {
	flippedDown = !flippedDown;
}

bool Card::intersects(const sf::Vector2f& translatedPos) {
	if (faceDownCardSprite.getGlobalBounds().contains(translatedPos))
		return true;
}

const bool Card::flippedUp() {
	return !flippedDown;
}

int Card::getCardValue() {
	return int(value);
}

string Card::getCardValName() {
	string ret;

	switch (value) {
	case CardValue::ACE:
		ret = "ace_of_";
		break;
	case CardValue::JACK:
		ret = "jack_of_";
		break;
	case CardValue::QUEEN:
		ret = "queen_of_";
		break;
	case CardValue::KING:
		ret = "king_of_";
		break;
	default:
		ret = to_string(int(value)) + "_of_";
		break;
	}
	return ret;
}

string Card::getCardSuiteName() {
	string ret;

	switch (suite) {
	case CardSuite::SPADES:
		ret = "spades";
		break;
	case CardSuite::DIAMONDS:
		ret = "diamonds";
		break;
	case CardSuite::HEARTS:
		ret = "hearts";
		break;
	case CardSuite::CLUBS:
		ret = "clubs";
		break;
	default:
		ret = "error, no suite";
		break;
	}

	ret += ".png";

	return ret;
}

void Card::render(sf::RenderTarget& target)
{
	if (flippedDown) {
		target.draw(faceDownCardSprite);
	}	
	else {
		target.draw(faceUpCardSprite);
	}
		
}
