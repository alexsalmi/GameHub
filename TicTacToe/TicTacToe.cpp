#include "TicTacToe.h"

// Constructor
TicTacToe::TicTacToe(){}

// Begin the TicTacToe application
void TicTacToe::start(){
	int menuChoice;

	// Show the menu screen until user quits out
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(false); break;   	// Singleplayer game
			case 2: play(true); break;		// 2 player game
			case 3: rules(); break;			// Rules
			default: break;
		}
	}while(menuChoice!=0);
}

// Main manu for tic tac toe options
int TicTacToe::menu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << "                        Welcome to Tic Tac Toe!                        \n" 
				"               Please select an option from the menu below:            \n" << endl;

		cout << "               (1) Play Tic Tac Toe vs. the CPU    (1 Player)          \n" 
				"               (2) Play Tic Tac Toe vs. a friend   (2 Player)          \n"
				"               (3) View game rules and controls 				        \n"<< endl;

		cout << "               (0) Return to GameHub							        " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice <=3 && menuChoice >= 0){
			return menuChoice;		// Return the mune choice to start()
		}
	}
}

// Main game logic for tic tac toe
void TicTacToe::play(bool multiplayer){
	TTTBoard gameBoard;				// Create the game board
	bool gameOver = false;			// keep track of if the game is over
	int moveKey;					// input variable for character key inputs
	movesRemaining = size*size;		// set moves remaining to the number of places on the board
	Xturn = true;					// start game off as X's turn

	// Set seed for CPU random tile selection
	if(!multiplayer)
		srand((unsigned)time(0));
	// Start game loop
	while(!gameOver){
		// Print header and current game board to the cmd window, as well as change text attributes
		printHeader();
		gameBoard.print();
		ansi.textColor("green");
		cout << endl << endl;

		// Print out game info under game board
		if(Xturn && !multiplayer)
			cout << "                              Your turn!                               " << endl;
		else if(!Xturn && !multiplayer)
			cout << "                              CPU's turn                               " << endl;
		else if(Xturn && multiplayer)
			cout << "                               X's turn                                " << endl;
		else if(!Xturn && multiplayer)
			cout << "                               O's turn                                " << endl;

			cout << "     [Arrow Keys] - Move     [Spacebar] - Place X/O     [q] - Quit     " << endl;

		ansi.textReset();

		// CPU's turn 
		if(!multiplayer && !Xturn){
			// Pick a random available space on the board
			int space = rand()%(movesRemaining);
			// Find the position on the board, ignoring occupied spaces
			for(int i=0; i<size*size; i++){
				if(gameBoard.isEmpty(i)){			// isEmpty checks if spot i on the board is available
					if(space == 0){
						Sleep(1000);				// Sleep for 1s for immersion
						gameBoard.placeCPU(i);		// Place the 'O' on the board
						Xturn = !Xturn;				// Update to next turn in game
						movesRemaining--;
						break;
					}
					else
						space--;
				}
			}
		}
		else{
			// Get character key input from user and update the gameboard accordingly
			moveKey = getch();
			gameBoard.update(moveKey, Xturn);
			if(moveKey==' '){			// If User pressed spacebar, update to next turn in game
				Xturn = !Xturn;
				movesRemaining--;
			}
			else if(moveKey=='q')		// If user pressed 'q', quit out of the game
				gameOver=true;
		}
		
		// Check if game is over, and if it is, move to the endgame screen
		Winner winner = isGameOver(gameBoard, multiplayer);
		if(winner!=NA){
			gameOver=true;
			endgame(winner, gameBoard);
		}
	}
}

//Checks if the game is over and finds out who won
Winner TicTacToe::isGameOver(TTTBoard gameBoard, bool multiplayer){
	// Checking for diagonal 3 in a rows
	if(gameBoard.board[0]==gameBoard.board[4] && gameBoard.board[0]==gameBoard.board[8] ||
		gameBoard.board[2]==gameBoard.board[4] && gameBoard.board[2]==gameBoard.board[6]){
		if(gameBoard.board[4]=='X'){
			if(multiplayer)return X;
			else return Player;
		}
		else if(gameBoard.board[4]=='O'){
			if(multiplayer)return O;
			else return CPU;
		}
	}

	for(int i=0; i<size; i++){
		// Checking for horizontal 3 in a rows
		if(gameBoard.board[0+i*size]==gameBoard.board[1+i*size] && gameBoard.board[0+i*size]==gameBoard.board[2+i*size]){
			if(gameBoard.board[0+i*size]=='X'){
				if(multiplayer)return X;
				else return Player;
			}
			else if(gameBoard.board[0+i*size]=='O'){
				if(multiplayer)return O;
				else return CPU;
			}
		}
		// Checking for vertical 3 in a rows
		else if(gameBoard.board[i+0*size]==gameBoard.board[i+1*size] && gameBoard.board[i+0*size]==gameBoard.board[i+2*size]){
			if(gameBoard.board[i+0*size]=='X'){
				if(multiplayer)return X;
				else return Player;
			}
			else if(gameBoard.board[i+0*size]=='O'){
				if(multiplayer)return O;
				else return CPU;
			}
		}
	}
	// If none of the above winning conditions were met, and there are no free spaces 
	if(movesRemaining==0){
		return Draw;
	}
	return NA;
}

// Post game screen
void TicTacToe::endgame(Winner winner, TTTBoard gameBoard){
	// Print the board of the finished game and change text atrributes
	printHeader();
	gameBoard.print();	
	ansi.textColor("green");
	cout << endl << endl;

	// Print out who won the game
	if(winner == Draw)
		cout << "                         Bummer, it's a draw!                          " << endl;
	else if(winner == CPU)
		cout << "                           Sorry, you lost.                            " << endl;
	else{
		cout << "                        Congratulations, ";
		if(winner==X)
			cout << 'X';
		else if(winner==O)
			cout << 'O';
		else if(winner==Player)
			cout << "You";
		cout <<" won!                        " << endl;
	}

	// Exit to tic tac toe menu
	cout << endl;
	cout << "                   Press any key to return to the menu                    " << endl;
	getch();
	ansi.textReset();
}

// Print the header to the cmd window
void TicTacToe::printHeader(){
    ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+---------------------------------------------------------------------+\n"
			"|                                                                     |\n" 
			"|   XXXXX  XXXXX  XXXXX   XXXXX  XXXXX  XXXXX   XXXXX  XXXXX  XXXXX   |\n" 
			"|     X      X    X         X    X   X  X         X    X   X  X       |\n" 
			"|     X      X    X         X    XXXXX  X         X    X   X  XXX     |\n"
			"|     X      X    X         X    X   X  X         X    X   X  X       |\n"
			"|     X    XXXXX  XXXXX     X    X   X  XXXXX     X    XXXXX  XXXXX   |\n"
			"|                                                                     |\n"
			"+---------------------------------------------------------------------+\n" << endl;
	ansi.textReset();
}

void TicTacToe::rules(){
	printHeader();
	ansi.textColor("green");
	cout << "                                RULES:                                 \n" << endl;
	
	cout << "Tic tac toe is a two player game, each playing either X or O, where the\n" 
			"players take turns to place their character in a 3x3 grid. The player  \n"
			"who gets three of their characters in a row first wins. The three char-\n"
			"acters can be horizontal, vertical, or diagonal.						\n"
			"If you choose to play single player, you will play against the computer.\n"
			"You will play as X, the cpu will be O.									\n"
			"If you choose to play 2 player, you will take turns playing as X and O.\n"
			"X will start the game. 												\n" << endl;

	cout << "                              CONTROLS:                                \n" << endl;

	cout << "                      [Arrow keys] - Move cursor                       \n"
			"                       [Spacebar]  - Place X/O characters              \n\n" << endl;

	cout << "                  Press any key to return to the menu                  \n" << endl;
	getch();
	ansi.textReset();
}