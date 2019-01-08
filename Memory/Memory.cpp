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
			case 11: play(e); break;				// Play Memory on Easy Difficulty
			case 12: play(m); break;				// Play Memory on Medium Difficulty
			case 13: play(h); break;				// Play Memory on Hard Difficulty
			case 2: rules(); break;				// Rules of Memory
			default: break;
		}
	}while(menuChoice!=0);
}

// Displays menu and takes input from user
int Memory::menu(){
	int menuChoice;
	bool diffMenu = false;
	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << endl;
		cout << "                                           Welcome to Memory!                                      \n" 
				"                             Please select an option from the menu below:                          \n" << endl << endl;

		if(!diffMenu){
			cout << "                             (1) Play Memory                                                       \n" << endl;
			
			cout <<	"                             (2) View game rules and controls\n" << endl;

			cout << "                             (0) Return to GameHub							                         " << endl;
			ansi.textReset();
		}
		else{
			ansi.textAttr("-bold");
			cout << "                             ( ) Play Memory                                                       \n";
			ansi.textAttr("bold");
			cout << "                             (1) Easy | (2) Medium | (3) Hard       			                    \n"<< endl;

			cout << "                             (0) Return to menu							                         " << endl;
			ansi.textReset();
		}

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(!diffMenu){
			if(menuChoice == 1)
				diffMenu = true;
			else if(menuChoice<=2 && menuChoice>=0)
				return menuChoice;		// Return the mune choice to start()
		}
		else if(menuChoice<=3 && menuChoice>=0){
			if(menuChoice == 0)
				diffMenu = false;
			else if(menuChoice<=3 && menuChoice>=1)
				return menuChoice + 10;
		}
	}
}

// Main game loop 
void Memory::play(Difficult diff){
	bool gameOver = false;			// keep track of if the game is over
	int moveKey;					// input variable for character key inputs
	MemoryBoard* gameBoard;

	// Create the game board based on difficulty
	if(diff==e)
		gameBoard = new MemoryBoard(3, 3);
	else if(diff==m)
		gameBoard = new MemoryBoard(5, 5);
	else if(diff==h)
		gameBoard = new MemoryBoard(7, 7);

	int pairs = gameBoard->pairsLeft; // number of pairs left to be matched

	while(gameBoard->pairsLeft>0){
		// Print header and current game board to the cmd window, as well as change text attributes
		printHeader();
		gameBoard->print();
		ansi.textColor("green");
		ansi.textAttr("bold");
		cout << "\n";

		switch(gameBoard->choice){
			case first:
				cout << "                                      Choose your first tile                                       " << endl;
				break;
			case second:
				cout << "                                      Choose your second tile                                     " << endl;
				break;
			case waitingSuccess:
				cout << "                             That's a match! Press any button to continue                          " << endl;
				break;
			case waitingFail:
				cout << "                          Bummer, not a match. Press any button to continue                        " << endl;
				break;

		}
		cout << "\n";
		cout << "                                        Pairs remaining: " << gameBoard->pairsLeft << endl;
		cout << "\n\n";
		ansi.textAttr("-bold");
		cout << "                  [Arrow Keys] - Move     [Spacebar] - Choose tile     [q] - Quit                  " << endl;

		ansi.textReset();

		// Get character key input from user and update the gameboard accordingly
		moveKey = getch();		
		if(moveKey==224)
			moveKey = getch();
		gameBoard->update(moveKey);

		if(moveKey=='q')
			return;
	}

	endgame(*gameBoard);
	delete gameBoard;
}
// Displays post game screen
void Memory::endgame(MemoryBoard gameBoard){
	printHeader();
	gameBoard.print();

	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "\n\n\n";
	cout << "                                Congratulations, you won! Good memory                                " << endl;

	// Exit to memory menu
	cout << "\n\n\n";
	cout << "                                 Press any key to return to the menu                                 " << endl;
	getch();
	ansi.textReset();
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