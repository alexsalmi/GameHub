#include "Memory.h"

// Constructor
Memory::Memory(){}

// Function for starting the game 
void Memory::start(){
	int menuChoice;

	// Show the menu screen until user quits out
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(); break;				// Play Memory
			case 2: rules(); break;				// Rules of Memory
			default: break;
		}
	}while(menuChoice!=0);
}

// Displays menu and takes input from user
int Memory::menu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << endl;
		cout << "                                           Welcome to Memory!                                      \n" 
				"                             Please select an option from the menu below:                          \n" << endl << endl;

		cout << "                             (1) Play Memory                                                       \n" << endl;
		
		cout <<	"                             (2) View game rules and controls\n" << endl;

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
void Memory::play(){
	MemoryBoard gameBoard;			// Create the game board
	bool gameOver = false,			// keep track of if the game is over
		didPlace;					// keep track of whether the a move was made on calling the TTTboard function update()
	int moveKey;					// input variable for character key inputs

	while(!gameOver){
		// Print header and current game board to the cmd window, as well as change text attributes
		printHeader();
		gameBoard.print();
		ansi.textColor("green");
		ansi.textAttr("bold");
		cout << "\n\n\n";

		cout << "                                      Choose your first tile.                                     " << endl;
		cout << "                            Press any key to return to the Memory menu.                           " << endl;

		ansi.textReset();

		// Get character key input from user and update the gameboard accordingly
		moveKey = getch();
		return;
		
	}

}

// Prints memory header to cmd window
void Memory::printHeader(){
    ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+-------------------------------------------------------------------------------------------------+\n"
			"|                                                                                                 |\n" 
			"|                            XXXXX  XXXXX  XXXXX  XXXXX  XXXXX  X   X                             |\n" 
			"|                            X X X  X      X X X  X   X  X   X  X   X                             |\n" 
			"|                            X X X  XXX    X X X  X   X  XXXXX  XXXXX                             |\n"
			"|                            X X X  X      X X X  X   X  XXXX     X                               |\n"
			"|                            X X X  XXXXX  X X X  XXXXX  X   X    X                               |\n"
			"|                                                                                                 |\n"
			"+-------------------------------------------------------------------------------------------------+\n" << endl;
	ansi.textReset();

}

// Displays the rules of the game
void Memory::rules(){

}