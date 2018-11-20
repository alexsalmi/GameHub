#include "TicTacToe/TicTacToe.h"

using namespace std;

dispANSI ansi;
string _name;

void printTitle();
string mainScreen();
int mainMenu();

int main(){
	system("CLS");
	_name = mainScreen();

	int menuChoice;
	do{
		menuChoice = mainMenu();

		switch(menuChoice){
			case 1: 
				TicTacToe game;
				game.start();
				delete &game;
				break;
		}

	}while(menuChoice!=0);

	ansi.textReset();
	ansi.clearScreen();

	return 0;
}

string mainScreen(){
	string name;
	printTitle();
    ansi.textColor("green");
	cout << " |          Version 1.0          |    Created By: Alexander Salmi    |" << endl;
	cout << " \\_______________________________|___________________________________/" << endl;
	cout << endl << endl << endl;
	ansi.textAttr("bold");
	cout << "                       Enter your name to begin: ";

	cin >> name; 
	ansi.textReset();
	return name;
}

int mainMenu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printTitle();
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << "               Welcome to GameHub, " << _name << "!                    \n" 
				"               What game would you like to play?                       \n" << endl;

		cout << "               (1) Tic Tac Toe                                         \n"
				"               ( ) More games coming soon!   				        \n"<< endl;

		cout << "               (0) Quit GameHub							        " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice <= 1 || menuChoice >= 0)
			return menuChoice;		
	}
}

void printTitle(){
    ansi.clearScreen();
    ansi.textAttr("bold");
    ansi.textColor("green");
		cout << "  ___________________________________________________________________  \n"
				"//                                                                   \\\\\n"
				"++-------------------------------------------------------------------++\n"
				"||    XXXXXXXX                           XXX  XXX                    ||\n"
				"||    XXXXXXXX  XXXXXX  XXX XXX  XXXXXX  XXX  XXX  X    X  XXXXX     ||\n"
				"||    XXX       X    X  X  X  X  X       XXX  XXX  X    X  X    X    ||\n"
				"||    XXX XXXX  XXXXXX  X  X  X  XXXX    XXXXXXXX  X    X  XXXXX     ||\n"
				"||    XXX   XX  X    X  X  X  X  X       XXXXXXXX  X    X  X    X    ||\n"
				"||    XXXXXXXX  X    X  X  X  X  XXXXXX  XXX  XXX  XXXXXX  XXXXX     ||\n"
				"||    XXXXXXXX                           XXX  XXX                    ||\n"
				"++-------------------------------------------------------------------++\n"
				"\\\\___________________________________________________________________//\n" << endl;
	ansi.textReset();
}