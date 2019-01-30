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
			case 1: play(false); break;				// Play Mastermind in Single Player mode
			case 2: play(true); break;				// Play Mastermind in Multiplayer mode
			case 3: rules(); break;					// Rules of Mastermind
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

		cout << "                             (1) Play Mastermind vs. the CPU    (1 Player)                         \n"
				"                             (2) Play Mastermind vs. a friend   (2 Player)                         \n" << endl;
		
		cout << "                             (3) View game rules and controls\n" << endl;

		cout << "                             (0) Return to GameHub							                         " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice<=3 && menuChoice>=0)
			return menuChoice;
	}

}

// Main game loop 
void Mastermind::play(bool mult){
	int moveKey;
	multiplayer = mult;
	int i, color;

	if(!multiplayer){
		srand((unsigned)time(0));
		for(i=0; i<solLength; i++){
			color = rand()%NUM_OF_COLORS;
			switch(color){
				case 0: solution[i] = "red"; break;
				case 1: solution[i] = "blue"; break;
				case 2: solution[i] = "green"; break;
				case 3: solution[i] = "yellow"; break;
				case 4: solution[i] = "white"; break;
				case 5: solution[i] = "cyan"; break;
			}
		}
	}
	else{
		bool isDone = false;
		while(!isDone){
			printHeader();
			ansi.textColor("green");
			ansi.textAttr("bold");

			cout << "                        Player 1, choose a pattern for your opponent to guess:               \n" << endl;

			cout << "                                         ";
			for(i=0; i<solLength; i++){
				if(currentChoice==i)
					ansi.textColor(colorChoice);
				else if(currentChoice>i)
					ansi.textColor(solution[i]);
				else 
					ansi.textColor("black");
				cout << "O ";			
			}
			do{
				moveKey = getch();
				if(moveKey==224)
					moveKey = getch();
				if(moveKey=='q')
					return;
				if(moveKey==' '){
					solution[currentChoice] = colorChoice;
					currentChoice++;
					if(currentChoice==4){
						currentChoice = 0;
						isDone = true;
					}
				}
				else{
					makeMove(moveKey, NULL);
				}
			}while(moveKey!=KEY_LEFT && moveKey!=KEY_RIGHT && moveKey!=' ' && moveKey!='u');
		}
	}

	MMBoard *gameBoard = new MMBoard(solution);

	while(turnsLeft>0){
		printHeader();
		gameBoard->print();
		ansi.textColor("green");
		ansi.textAttr("bold");

		cout << "                                         ";
		for(i=0; i<solLength; i++){
			if(currentChoice==i)
				ansi.textColor(colorChoice);
			else if(currentChoice>i)
				ansi.textColor(guess[i]);
			else 
				ansi.textColor("black");
			cout << "O ";			
		}

		ansi.textColor("green");
		cout << "\n\n"
				"                                       Choose your next color\n\n";

		ansi.textAttr("-bold");
		cout << "   [Arrow Keys] - Cycle between colors   [Spacebar] - Choose color   [u] - Undo move   [q] - Quit  " << endl;

		do{
			moveKey = getch();
			if(moveKey==224)
				moveKey = getch();
			if(moveKey=='q')
				return;
		}while(moveKey!=KEY_LEFT && moveKey!=KEY_RIGHT && moveKey!=' ' && moveKey!='u');

		makeMove(moveKey, gameBoard);

		if((gameBoard->isGameOver(guess) && currentChoice==0) || gameBoard->currentGuess == 7){
			endgame(gameBoard);
			delete gameBoard;
			return;
		}
	}

}

// Make a move based on user's key press
void Mastermind::makeMove(int moveKey, MMBoard* gameBoard){
	switch(moveKey){
		case KEY_RIGHT:
			colorIndex = (colorIndex+1)%NUM_OF_COLORS;
			colorChoice = colors[colorIndex];
			break;
		case KEY_LEFT:
			if(colorIndex==0)
				colorIndex = NUM_OF_COLORS;
			colorIndex = colorIndex-1;
			colorChoice = colors[colorIndex];
			break;
		case 'u':
			if(currentChoice>0){
				currentChoice--;
				colorChoice = guess[currentChoice];
			}
			break;
		case ' ':
			guess[currentChoice] = colorChoice;
			currentChoice++;
			break;
	}
	if(currentChoice==4){
		currentChoice=0;
		gameBoard->update(guess);
	}
}

// Displays post game screen
void Mastermind::endgame(MMBoard *gameBoard){
	// Print the board of the finished game and change text atrributes
	printHeader();
	gameBoard->print();	
	ansi.textColor("green");
	ansi.textAttr("bold");

	// Print out who won the game
	if(!multiplayer)
		cout << "                              Congratulations, you guessed the pattern!                            " << endl;
	else{
		if(!gameBoard->isGameOver(guess))
			cout << "                 Sorry player 2, you couldn't guess the pattern. Player 1, you win!                " << endl;
		else
			cout << "                             You guessed the pattern, player 2, you win!                           " << endl;

	}

	// Exit to tic tac toe menu
	ansi.textAttr("-bold");
	cout << "\n\n";
	cout << "                                 Press any key to return to the menu                                 " << endl;
	getch();
	ansi.textReset();
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
	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "                                              RULES:                                               \n" << endl;
	ansi.textAttr("-bold");
	
	cout << "              Mastermind is a game where a player must guess a pattern of four colors              \n" 
			"              in their correct order in a certain number of attempts. Each time the                \n"
			"              player makes a guess, they will recieve feedback on their guessed colors.            \n"
			"              If the feedback for a color is red, this means that the color does not               \n"
			"              exist in the pattern. If it is white, this means the color exists in the             \n"
			"              pattern, but is in the wrong place in the order. If it is green, this means          \n"
			"              the guessed color is correct. If the player does not guess the correct               \n"
			"              pattern after 7 turns, they lose.                                                    \n"
			"              If you play a single player game, the game will choose a pattern for you             \n"
			"              to guess automatically. If you play a multiplayer game, player 1 will choose         \n"
			"              the pattern, and player 2 must guess it.                                             \n"<< endl;
	
	ansi.textAttr("bold");
	cout << "                                            CONTROLS:                                              \n" << endl;
	ansi.textAttr("-bold");

	cout << "                            [Keyboard] - Choose between colors                           \n"
			"                            [Spacebar] - Select a color                                  \n"
			"                                   [u] - Undo a guessed color                            \n" << endl;

	ansi.textAttr("bold");

	cout << "                                Press any key to return to the menu                                \n" << endl;
	ansi.textAttr("-bold");
	getch();
	ansi.textReset();

}
