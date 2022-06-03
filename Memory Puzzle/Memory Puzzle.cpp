#include "Game.h"

using namespace std;

void displayRules() {
	cout << "\t\t\t\t\tWelcome to the Memory Puzzle!\n\n";
	cout << "Rules : " << endl;
	cout << "1. Earned points double if you match cards consecutively." << endl;
	cout << "2. If you do not pick 2 cards before the 5 second timer\n   on the bottom of the screen, it is the next players turn.\n\n\n";
}
int main()
{
	srand(static_cast<unsigned>(time(0)));

	displayRules();

	//Get player names;	
	string p1, p2;
	
	cout << "\t\t\t\t\tEnter Player 1's name : ";
	cin >> p1;
	cout << "\n\t\t\t\t\tEnter Player 2's name : ";
	cin >> p2;
	
	//Game loop
	Game game(p1,p2);

	while (game.running()) {
		game.update();
		game.render();
	}

	return 0;
}