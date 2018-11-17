#include "TicTacToe/TicTacToe.h"

using namespace std;

void printTitle();
string mainScreen();
void mainMenu();

int main(){
	system("CLS");
	string name = mainScreen();

	mainMenu();

	return 0;
}

string mainScreen(){
	string name;
	printTitle();
	cout << " |          Version 1.0          |    Created By: Alexander Salmi    |" << endl;
	cout << " \\_______________________________|___________________________________/" << endl;
	cout << endl << endl << endl;
	cout << "                       Enter your name to begin: ";

	cin >> name; 
	return name;
}

void mainMenu(){
	printTitle();

	TicTacToe game;
	game.start();
	delete &game;
}

void printTitle(){
    std::cout << "\x1b[2J";
		cout << "  ___________________________________________________________________  " << endl;
		cout << "//                                                                   \\\\" << endl;
		cout << "++-------------------------------------------------------------------++" << endl;
		cout << "||    XXXXXXXX                           XXX  XXX                    ||" << endl;
		cout << "||    XXXXXXXX  XXXXXX  XXX XXX  XXXXXX  XXX  XXX  X    X  XXXXX     ||" << endl;
		cout << "||    XXX       X    X  X  X  X  X       XXX  XXX  X    X  X    X    ||" << endl;
		cout << "||    XXX XXXX  XXXXXX  X  X  X  XXXX    XXXXXXXX  X    X  XXXXX     ||" << endl;
		cout << "||    XXX   XX  X    X  X  X  X  X       XXXXXXXX  X    X  X    X    ||" << endl;
		cout << "||    XXXXXXXX  X    X  X  X  X  XXXXXX  XXX  XXX  XXXXXX  XXXXX     ||" << endl;
		cout << "||    XXXXXXXX                           XXX  XXX                    ||" << endl;
		cout << "++-------------------------------------------------------------------++" << endl;
		cout << "\\\\___________________________________________________________________//" << endl;
}