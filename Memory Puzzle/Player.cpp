#include "Player.h"
using namespace std;

Player::Player(){
	initVariables();
}

void Player::initVariables() {
	points = 0;
}

//Get Functions
string Player::getName() {
	return name;
}

void Player::setName(const string& n) {
	name = n;
}

int Player::getPoints() {
	return points;
}

void Player::incrementPoint(const int &add) {
	points += add;
}
