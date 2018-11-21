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
			case 11: play(false, easy); break;   	// Singleplayer game (Easy)
			case 12: play(false, medium); break;   	// Singleplayer game (Medium)
			case 13: play(false, hard); break;   	// Singleplayer game (Hard)
			case 2: play(true, multiplayer); break;		// 2 player game
			case 3: rules(); break;			// Rules
			default: break;
		}
	}while(menuChoice!=0);
}

// Main manu for tic tac toe options
int TicTacToe::menu(){
	int menuChoice;
	bool diffMenu = false;
	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << "                        Welcome to Tic Tac Toe!                        \n" 
				"               Please select an option from the menu below:            \n" << endl;

		if(!diffMenu){
			cout << "               (1) Play Tic Tac Toe vs. the CPU    (1 Player)          \n"
					"               (2) Play Tic Tac Toe vs. a friend   (2 Player)          \n"
					"               (3) View game rules and controls 				        \n"<< endl;

			cout << "               (0) Return to GameHub							        " << endl;
			ansi.textReset();
		}
		else{
			ansi.textAttr("-bold");
			cout << "               ( ) Play Tic Tac Toe vs. the CPU                        \n";
			ansi.textAttr("bold");
			cout <<	"               Please choose a difficulty:					            \n"
					"               (1) Easy | (2) Medium | (3) Hard       			        \n"<< endl;

			cout << "               (0) Return to menu							        " << endl;
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
			else if(menuChoice<=3 && menuChoice>=0)
				return menuChoice;		// Return the mune choice to start()
		}
		else{
			if(menuChoice == 0)
				diffMenu = 0;
			else if(menuChoice<=3 && menuChoice>=1)
				return menuChoice + 10;
		}
	}
}

// Main game logic for tic tac toe
void TicTacToe::play(bool multiplayer, Difficulty diff){
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
		ansi.textAttr("bold");
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
		ansi.textAttr("-bold");

			cout << "     [Arrow Keys] - Move     [Spacebar] - Place X/O     [q] - Quit     " << endl;

		ansi.textReset();

		// CPU's turn 
		if(!multiplayer && !Xturn){
			gameBoard.placeCPU(cpuTurn(diff, gameBoard));
		}
		else{
			// Get character key input from user and update the gameboard accordingly
			moveKey = getch();
			if(moveKey == 224)
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

// Simulates the CPU's turn based on the chosen difficulty
int TicTacToe::cpuTurn(Difficulty diff, TTTBoard gameBoard){
	// If difficulty is set to hard, the cpu should place at a space that will immediately 
	// win them the game or block the player from winning
	if(diff == medium || diff == hard){
		// Search for spaces that will immediately win the game for the cpu
		int space = winningMove('O', gameBoard);
		if(space>=0){
			Sleep(1000);				// Sleep for 1s for immersion
			Xturn = !Xturn;				// Update to next turn in game
			movesRemaining--;
			return space;
		}

		// Search for spaces that will block the player from winning
		space = winningMove('X', gameBoard);
		if(space>=0){
			Sleep(1000);				// Sleep for 1s for immersion
			Xturn = !Xturn;				// Update to next turn in game
			movesRemaining--;
			return space;
		}
	}

	if(diff == hard){
		if(movesRemaining == 8){
			if(gameBoard.board[4] == 'X'){
				Sleep(1000);				// Sleep for 1s for immersion
				Xturn = !Xturn;				// Update to next turn in game
				movesRemaining--;
				return 0;
			}
			else{
				Sleep(1000);				// Sleep for 1s for immersion
				Xturn = !Xturn;				// Update to next turn in game
				movesRemaining--;
				return 4;
			}
		}

		if(movesRemaining == 6 && gameBoard.board[4]=='X' && gameBoard.board[8]=='X'){
			Sleep(1000);				// Sleep for 1s for immersion
			Xturn = !Xturn;				// Update to next turn in game
			movesRemaining--;
			return 6;
		}
	}

	// Pick a random available space on the board
	int space = rand()%(movesRemaining);
	// Find the position on the board, ignoring occupied spaces
	for(int i=0; i<size*size; i++){
		if(gameBoard.isEmpty(i)){			// isEmpty checks if spot i on the board is available
			if(space == 0){
				Sleep(1000);				// Sleep for 1s for immersion
				Xturn = !Xturn;				// Update to next turn in game
				movesRemaining--;
				return i;
			}
			else
				space--;
		}
	}
	return -1;
}

// Find potential winning moves for character, returns the index
int TicTacToe::winningMove(char character, TTTBoard gameBoard){
	// Checking for potential diagonal 3 in a rows
	if(gameBoard.board[0]==gameBoard.board[4] && gameBoard.board[0] == character && gameBoard.board[8]==' ')
		return 8;
	else if(gameBoard.board[0]==gameBoard.board[8] && gameBoard.board[0] == character && gameBoard.board[4]==' ')
		return 4;
	else if(gameBoard.board[4]==gameBoard.board[8] && gameBoard.board[4] == character && gameBoard.board[0]==' ')
		return 0;
	else if(gameBoard.board[2]==gameBoard.board[4] && gameBoard.board[2] == character && gameBoard.board[6]==' ')
		return 6;
	else if(gameBoard.board[2]==gameBoard.board[6] && gameBoard.board[2] == character && gameBoard.board[4]==' ')
		return 4;
	else if(gameBoard.board[4]==gameBoard.board[6] && gameBoard.board[4] == character && gameBoard.board[2]==' ')
		return 2;

	// Checking for potential horizontal and vertical 3 in a rows
	for(int i=0; i<size; i++){
		//  Horizontal
		if(gameBoard.board[0+i*size]==gameBoard.board[1+i*size] && gameBoard.board[0+i*size] == character && gameBoard.board[2+i*size]==' ')
			return 2+i*size;
		if(gameBoard.board[0+i*size]==gameBoard.board[2+i*size] && gameBoard.board[0+i*size] == character && gameBoard.board[1+i*size]==' ')
			return 1+i*size;
		if(gameBoard.board[1+i*size]==gameBoard.board[2+i*size] && gameBoard.board[1+i*size] == character && gameBoard.board[0+i*size]==' ')
			return 0+i*size;

		// Vertical
		if(gameBoard.board[i+0*size]==gameBoard.board[i+1*size] && gameBoard.board[i+0*size] == character && gameBoard.board[i+2*size]==' ')
			return i+2*size;
		if(gameBoard.board[i+0*size]==gameBoard.board[i+2*size] && gameBoard.board[i+0*size] == character && gameBoard.board[i+1*size]==' ')
			return i+1*size;
		if(gameBoard.board[i+1*size]==gameBoard.board[i+2*size] && gameBoard.board[i+1*size] == character && gameBoard.board[i+0*size]==' ')
			return i+0*size;
	}

	return -1;
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
	ansi.textAttr("bold");
	cout << "                                RULES:                                 \n" << endl;
	ansi.textAttr("-bold");
	
	cout << "Tic tac toe is a two player game, each playing either X or O, where the\n" 
			"players take turns to place their character in a 3x3 grid. The player  \n"
			"who gets three of their characters in a row first wins. The three char-\n"
			"acters can be horizontal, vertical, or diagonal.						\n"
			"If you choose to play single player, you will play against the computer.\n"
			"You will play as X, the cpu will be O.									\n"
			"If you choose to play 2 player, you will take turns playing as X and O.\n"
			"X will start the game. 												\n" << endl;

	ansi.textAttr("bold");
	cout << "                              CONTROLS:                                \n" << endl;
	ansi.textAttr("-bold");

	cout << "                      [Arrow keys] - Move cursor                       \n"
			"                       [Spacebar]  - Place X/O characters              \n\n" << endl;

	ansi.textAttr("bold");
	cout << "                  Press any key to return to the menu                  \n" << endl;
	ansi.textAttr("-bold");
	getch();
	ansi.textReset();
}