#include "Game.h"

using namespace std;

Game::Game(const string& p1, const string& p2)
{
	initVariables();
	initWindow();
	initPlayers(p1, p2);
	initBackground();
	initFont();
	initText();
	spawnCards();
}

Game::~Game()
{
	delete window;

	for (auto i : playingCards)
		delete i;
}


void Game::initWindow() {
	videoMode = sf::VideoMode(windowX, windowY);
	window = new sf::RenderWindow(videoMode, "Memory Puzzle", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(144);
}
void Game::initPlayers(const string &p1, const string &p2) {
	player1.setName(p1);
	player2.setName(p2);

	playerTurn = &player1;
}

void Game::setPlayerNames(const string& p1, const string& p2) {
	player1.setName(p1);
	player2.setName(p2);
}

void Game::initVariables() {
	endGame = false;
	playerOnesTurn = true;
	maxCards = 18;
	xGapOfCards = 185.f;
	yGapOfCards = 200.f;

	timerMax = 5;

	cardsFlipped = 0;

	pointGain = 5000;
	pointMultiplier = 1;
}

void Game::initBackground() {
	if (!guiBackGroundTexture.loadFromFile("Game_Sprites\\Background\\Black_wallpaper.jpg"))
		cout << "failed to load background" << endl;
	
	guiBackGround.setTexture(guiBackGroundTexture);
}

void Game::initFont() {
	if (!font.loadFromFile("Fonts/papernotes.ttf"))
		cout << "failed to load phenomicon font" << endl;
}

void Game::initText() {
	//Title
	titleText.setFont(font);
	titleText.setCharacterSize(50);
	titleText.setString("Memory Puzzle");
	titleText.setOrigin(titleText.getGlobalBounds().width / 2, titleText.getGlobalBounds().height / 2);
	titleText.setPosition(sf::Vector2f(float(windowX / 2), 20.f));

	//player 1 score
	p1Text.setFont(font);
	p1Text.setCharacterSize(32);
	p1Text.setString(player1.getName() + " : " + to_string(player2.getPoints()));
	p1Text.setPosition(sf::Vector2f(50.f, float(windowY - 50)));

	//player 2 score
	p2Text.setFont(font);
	p2Text.setCharacterSize(32);
	p2Text.setString(player2.getName() + " : " + to_string(player2.getPoints()));
	p2Text.setPosition(sf::Vector2f(float(windowX - p2Text.getGlobalBounds().width - 50), float(windowY - 50)));

	//Timer
	timerText.setFont(font);
	timerText.setCharacterSize(50);
	timerText.setFillColor(sf::Color::Red);
	timerText.setOrigin(timerText.getGlobalBounds().width / 2, timerText.getGlobalBounds().height / 2);
	timerText.setPosition(sf::Vector2f(float(windowX / 2 - 10), float(windowY - 75)));

	//EndGameText
	endGameText.setFont(font);
	endGameText.setCharacterSize(100);

	//Point display Text
	pointDisplayText.setFont(font);
	pointDisplayText.setCharacterSize(32);
}

void Game::pollEvents() {
	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		case sf::Event::MouseButtonPressed:
			updateMouse();
			break;
		}
	}
}

const bool Game::running() const {
	return window->isOpen();
}

//Object Functions

void Game::spawnCards() {
	float x = 85.f;
	float y = 75.f;
	float cardWidth = 125;
	
	randomizeCards();
	int index = 0;
	for (int i = 0; i < maxCards;++i) {
		int val = pairValSuite[i].first;
		int suite = pairValSuite[i].second;

		playingCards.push_back(new Card(x, y, val, suite));

		//card Movement
		if (x + cardWidth< windowX - cardWidth) {
			x += xGapOfCards;
		}
		else {
			x =85.f;
			y += yGapOfCards;
		}
	}
}

void Game::randomizeCards() {
	for (int i = 0; i < 13; ++i) {
		pairValSuite.push_back(make_pair(i + 1, rand() % 4 + 1));
	}

	random_shuffle(pairValSuite.begin(), pairValSuite.end(), [](int i) {return rand() % i; });
	pairValSuite.erase(pairValSuite.begin() + 9, pairValSuite.end());

	for (int i = 0; i < 9; ++i) {
		const int val = pairValSuite[i].first;
		const int suite = pairValSuite[i].second;

		int n = rand() % 4 + 1;

		while (n == suite) {
			n = rand() % 4 + 1;
		}

		pairValSuite.push_back(make_pair(val, n));
	}

	random_shuffle(pairValSuite.begin(), pairValSuite.end(), [](int i) {return rand() % i; });
}

void Game::switchPlayerTurn() {
	pointMultiplier = 1;
	if (playerOnesTurn) {
		playerTurn = &player2;
		playerOnesTurn = false;
	}
	else {
		playerTurn = &player1;
		playerOnesTurn = true;
	}

}
void Game::updateCards(){
	//for (auto i : playingCards)
	//	i->update();

	for (auto i : playingCards) {
		if (!i->flippedUp()) return;
	}

	//if all cards are flippedUp:
	endGame = true;
}
void Game::updateTimers() {
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= timerMax) {
		clock.restart();
		switchPlayerTurn();
		for (auto i : faceUpCardPair)
			i->flipCard();
		faceUpCardPair.clear();
		//dont restart, kill player
	}
	
}
void Game::updateGui() {
	stringstream ss;

	ss << timerMax - floor(elapsed.asSeconds());
	timerText.setString(ss.str());
	ss.clear();
	ss.str(string());

	//Players

	if (playerOnesTurn) {
		p1Text.setFillColor(sf::Color::Green);
		p2Text.setFillColor(sf::Color::White);
	}
	else {
		p2Text.setFillColor(sf::Color::Green);
		p1Text.setFillColor(sf::Color::White);
	}
	ss << player1.getName() << " : " << player1.getPoints();
	p1Text.setString(ss.str());
	ss.clear();
	ss.str(string());

	p2Text.setPosition(sf::Vector2f(float(windowX - p2Text.getGlobalBounds().width - 50), float(windowY - 50)));
	ss << player2.getName() << " : " << player2.getPoints();
	p2Text.setString(ss.str());
	ss.clear();
	ss.str(string());
}

void Game::updateMouse() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		auto translatePos = window->mapPixelToCoords(mousePos);

		bool found = false;
		for (auto i : playingCards) {
			if (i->intersects(translatePos) && !i->flippedUp()) {
				i->flipCard();
				found = true;
				faceUpCardPair.push_back(i);
			}
			if (found) break;
		}

		if (faceUpCardPair.size() == maxCardsFlipped) {
			update();
			render();

			updatePoints();
			faceUpCardPair.clear();
		}
	}
}

void Game::updatePoints() {
	Card *firstCard = faceUpCardPair[0];
	Card *secondCard = faceUpCardPair[1];
	bool isWrong = false;

	if (firstCard->getCardValue() == secondCard->getCardValue()) {
		playerTurn->incrementPoint(pointMultiplier * pointGain);
		pointDisplayColor = sf::Color::Green;
		pointMultiplier *= 2;
	}
	else {
		isWrong = true;
		pointDisplayColor = sf::Color::Red;
		pointMultiplier = 1;
	}

	sf::Clock sleep;
	sf::Time sleepElapsed = sleep.getElapsedTime();
	while (sleepElapsed.asSeconds() < 1) {
		sleepElapsed = sleep.getElapsedTime();
		renderPointDisplay();
	}

	if (isWrong) {
		firstCard->flipCard();
		secondCard->flipCard();
		switchPlayerTurn();
	}

	clock.restart();
}
void Game::update()
{
	pollEvents();

	if (!endGame) {
		updateGui();
		updateCards();
		updateTimers();
	}

	//updateMouse();
	//update game objects:
}
void Game::renderPointDisplay() {
	pointDisplayText.setFillColor(pointDisplayColor);
	string message;

	if (playerOnesTurn) {
		//pointDisplayText.setPosition(sf::Vector2f(float(150 + p1Text.getGlobalBounds().width), float(windowY - 50)));
		pointDisplayText.setPosition(sf::Vector2f(float(280), float(windowY - 50)));
	}
	else {
		//pointDisplayText.setPosition(sf::Vector2f(float(windowX - p2Text.getGlobalBounds().width - pointDisplayText.getGlobalBounds().width - 150), float(windowY - 50)));
		pointDisplayText.setPosition(sf::Vector2f(float(windowX - 363), float(windowY - 50)));
	}

	if (pointMultiplier == 1) message = "WRONG";
	else message = "+" + to_string(pointMultiplier / 2 * pointGain);
	pointDisplayText.setString(message);
	renderPD();
}

void Game::renderPD() {
	window->clear();
	//Render game objects:


	renderGui();
	renderCards();
	window->draw(pointDisplayText);
	renderCards();
	window->display();
}

void Game::renderCards() {
	int j = 1;
	for (auto i : playingCards) {
		i->render(*window);
	}
}
void Game::renderGui() {
	window->draw(guiBackGround);
	window->draw(titleText);
	window->draw(p1Text);
	window->draw(p2Text);
	window->draw(timerText);
}

void Game::renderGameOver() {
	int winnersPoint = max(player1.getPoints(), player2.getPoints());
	
	stringstream gameOverMessage;
	sf::Color color;
	if (player1.getPoints() > player2.getPoints()) {
		color = p1Text.getFillColor();
		gameOverMessage << player1.getName() << " Won!";
	}
	else if (player2.getPoints() > player1.getPoints()) {
		color = p2Text.getFillColor();
		gameOverMessage << player2.getName() << " Won!";
	}
	else {
		color = sf::Color::Green;
		gameOverMessage << "Game Tied!";
	}

	sf::Rect<float> size = endGameText.getGlobalBounds();
	endGameText.setFillColor(color);
	endGameText.setOrigin(size.width / 2, size.height / 2);
	endGameText.setPosition(sf::Vector2f(float(windowX / 2 - 20), float(windowY / 2 - 30)));
	endGameText.setString(gameOverMessage.str());
	window->draw(endGameText);
}
void Game::render()
{
	window->clear();
	//Render game objects:


	renderGui();
	renderCards();
	if (endGame) {
		updateGui();
		renderGui();
		renderCards();
		renderGameOver();
	}
	window->display();

}

