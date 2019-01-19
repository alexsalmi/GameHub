#include "Mastermind.h"

//Constructor
Mastermind::Mastermind(){}

// Function for starting the game
void Mastermind::start(){
	int menuChoice;

	// Show the menu screen until user quits out
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(); break;				// Play Mastermind
			case 2: rules(); break;				// Rules of Mastermind
			default: break;
		}
	}while(menuChoice!=0);
}

int Mastermind::menu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << endl;
		cout << "                                      Welcome to Mastermind!                                       \n" 
				"                             Please select an option from the menu below:                          \n" << endl << endl;

		cout << "                             (1) Play Mastermind                                                   \n" << endl;
		
		cout << "                             (2) View game rules and controls\n" << endl;

		cout << "                             (0) Return to GameHub							                         " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice<=2 && menuChoice>=0)
			return menuChoice;
	}

}

// Main game loop 
void Mastermind::play(){

}

// Displays post game screen
void Mastermind::endgame(){

}

// Prints mastermind header to cmd window
void Mastermind::printHeader(){
    ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+-------------------------------------------------------------------------------------------------+\n"
			"|                                                                                                 |\n" 
			"|               XXXXX  XXXXX  XXXXX  XXXXX  XXXXX  XXXXX  XXXXX  XXXXX  X   X  XXXX               |\n" 
			"|               X X X  X   X  X        X    X      X   X  X X X    X    XX  X  X   X              |\n" 
			"|               X X X  XXXXX  XXXXX    X    XXX    XXXXX  X X X    X    X X X  X   X              |\n"
			"|               X X X  X   X      X    X    X      XXXX   X X X    X    X  XX  X   X              |\n"
			"|               X X X  X   X  XXXXX    X    XXXXX  X   X  X X X  XXXXX  X   X  XXXX               |\n"
			"|                                                                                                 |\n"
			"+-------------------------------------------------------------------------------------------------+\n" << endl;
	ansi.textReset();
}	

// Displays the rules of the game
void Mastermind::rules(){
}
