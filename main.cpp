// GameHub
// Author: Alex Salmi

#include "TicTacToe/TicTacToe.h"
#include "SimonSays/SimonSays.h"
#include "Memory/Memory.h"
#include "ConnectFour/ConnectFour.h"
#include "Hangman/Hangman.h"
#include "Mastermind/Mastermind.h"

using namespace std;

// For ansi escape commands
dispANSI ansi;

void printTitle();
void mainScreen();
int mainMenu();

int main(){
	// Prepare the window
	system("CLS");
	ansi.windowSize(100, 33);
	ansi.showCursor(false);

	// Print the welcome screen
	mainScreen();

	// Print the menu and get the user's menu choice, starting the corresponding game
	int menuChoice;
	// Menu loop
	do{
		// Print menu
		menuChoice = mainMenu();

		// Start the game corresponding to the user's input
		if(menuChoice==1){
			SimonSays* simonSays = new SimonSays();
			simonSays->start();
			delete simonSays;
		}
		else if(menuChoice==2){
			Memory* memory = new Memory();
			memory->start();
			delete memory;
		}
		else if(menuChoice==3){
			TicTacToe* ticTac = new TicTacToe();
			ticTac->start();
			delete ticTac;
		}
		else if(menuChoice==4){
			Mastermind* mastermind = new Mastermind();
			mastermind->start();
			delete mastermind;
		}
		else if(menuChoice==5){
			ConnectFour* connectfour = new ConnectFour();
			connectfour->start();
			delete connectfour;
		}
		else if(menuChoice==6){
			Hangman* hangman = new Hangman();
			hangman->start();
			delete hangman;
		}
	}while(menuChoice!=0);	// If the user enters 0, game is over

	// Reset the window
	ansi.textReset();
	ansi.clearScreen();
	ansi.showCursor(true);

	return 0;
}

// Prints the welcome screen
void mainScreen(){
	string name;
	printTitle();
    ansi.textColor("green");
	cout << " |                 Version 1.5                 |           Created By: Alex Salmi                |" << endl;
	cout << " \\_____________________________________________|_________________________________________________/" << endl;
	cout << "\n\n\n\n\n\n";
	ansi.textAttr("bold");

	// Wait for the user to press a key to enter app
	cout << "                                    Press any button to begin                                     " << endl;
	ansi.textReset();

	getch(); 	// Reads key presses
}

// Prints the menu
int mainMenu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printTitle();
		ansi.textColor("green");
		ansi.textAttr("bold");
		cout << "\n\n";

		// Print the menu options to the cmd window
		cout << "                                        Welcome to GameHub!                                        \n" 
				"                                 What game would you like to play?                               \n\n" << endl;

		cout << "                                 1-Player:         2-Player:                                       \n" << endl;

		cout << "                                 (1) Simon Says    (3) Tic Tac Toe                                 \n" 
				"                                 (2) Memory        (4) Mastermind                                  \n" 
				"                                 (3) Tic Tac Toe   (5) Connect Four                                \n"
				"                                 (4) Mastermind    (6) Hangman                                 \n\n\n" << endl;

		cout << "                                        (0) Quit GameHub			                                  " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice <= 5 && menuChoice >= 0)
			return menuChoice;		
	}
}

// Prints the header
void printTitle(){
    ansi.clearScreen();
    ansi.textAttr("bold");
    ansi.textColor("green");
		cout << "  _______________________________________________________________________________________________  \n"
				"//                                                                                               \\\\\n"
				"++-----------------------------------------------------------------------------------------------++\n"
				"||                  XXXXXXXX                           XXX  XXX                                  ||\n"
				"||                  XXXXXXXX  XXXXXX  XXX XXX  XXXXXX  XXX  XXX  X    X  XXXXX                   ||\n"
				"||                  XXX       X    X  X  X  X  X       XXX  XXX  X    X  X    X                  ||\n"
				"||                  XXX XXXX  XXXXXX  X  X  X  XXXX    XXXXXXXX  X    X  XXXXX                   ||\n"
				"||                  XXX   XX  X    X  X  X  X  X       XXXXXXXX  X    X  X    X                  ||\n"
				"||                  XXXXXXXX  X    X  X  X  X  XXXXXX  XXX  XXX  XXXXXX  XXXXX                   ||\n"
				"||                  XXXXXXXX                           XXX  XXX                                  ||\n"
				"++-----------------------------------------------------------------------------------------------++\n"
				"\\\\_______________________________________________________________________________________________//\n";
	ansi.textReset();
}