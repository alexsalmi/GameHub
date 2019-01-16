#include "ConnectFour.h"

// Constructor
ConnectFour::ConnectFour(){};

// Begin the Connect Four application
void ConnectFour::start(){
	int menuChoice;	

	// Show the menu screen until user quits out
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(); break;		// Play Connect Four
			case 2: rules(); break;		// Show the rules of Connect Four
			default: break;
		}
	}while(menuChoice!=0);
}

// Displays menu and takes input from user
int ConnectFour::menu(){ 
	int menuChoice;

	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << endl;
		cout << "                                       Welcome to Connect Four!                                    \n" 
				"                             Please select an option from the menu below:                          \n" << endl << endl;

		cout << "                             (1) Play Connect Four                                                 \n" << endl;
		
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
		else if(menuChoice<=2 && menuChoice>=0){
			return menuChoice;
		}
	}
}

// Main game loop
void ConnectFour::play(){
	CFBoard gameBoard;		// The game board 
	int moveKey;			// For reading key presses
	playerTurn = 1;			// Keep track of who's turn it is
	movesLeft = gameBoard.rows*gameBoard.cols;		// How many spaces are available on the board

	// Main game loop
	while(true){
		// Print the game screen, including board
		printHeader();
		gameBoard.print();
		ansi.textColor("green");
		ansi.textAttr("bold");
		cout << "\n\n";

		if(playerTurn==1)
			cout << "                                           Player 1";
		else
			cout << "                                           Player 2";

		cout << "'s turn\n\n";

		ansi.textAttr("-bold");
		cout << "                  [Arrow Keys] - Move     [Spacebar] - Choose tile     [q] - Quit                  " << endl;

		ansi.textReset();

		// Get character key input from user and update the gameboard accordingly
		moveKey = getch();		
		// For arrow key inputs
		if(moveKey==224)
			moveKey = getch();
		// If the player places a piece in a valid column
		if(gameBoard.update(moveKey, playerTurn)){
			movesLeft--;		// There is one less space available on the board
			int winner = isGameOver(gameBoard);	// Checks if the game is over, and saves the winner
			// If there is a winner, the game is over, print endgame screen
			if(winner!=0){
				endgame(gameBoard, winner);
				return;
			}
			// Update to the next players turn
			playerTurn = ((playerTurn)%2)+1;
		}

		// Quit the game
		if(moveKey=='q')
			return;
	}
}

// Checks if the game is over, and returns the winner if it is
int ConnectFour::isGameOver(CFBoard gameBoard){
	int r, c;
	// If there are no moves left on the board, it is a tie
	if(movesLeft==0)
		return 3;

	// Check for horizontal four in a rows, returning who won if one is found
	for (r=0; r<gameBoard.rows; r++){
		for(c=0; c<gameBoard.cols-3; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r][c+1] && gameBoard.board[r][c]==gameBoard.board[r][c+2] 
				&& gameBoard.board[r][c]==gameBoard.board[r][c+3] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}
	// Check for vertical four in a rows, returning who won if one is found
	for (r=0; r<gameBoard.rows-3; r++){
		for(c=0; c<gameBoard.cols; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r+1][c] && gameBoard.board[r][c]==gameBoard.board[r+2][c] 
				&& gameBoard.board[r][c]==gameBoard.board[r+3][c] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}
	// Check for diagonal four in a rows, returning who won if one is found
	for (r=0; r<gameBoard.rows-3; r++){
		for(c=0; c<gameBoard.cols-3; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r+1][c+1] && gameBoard.board[r][c]==gameBoard.board[r+2][c+2] 
				&& gameBoard.board[r][c]==gameBoard.board[r+3][c+3] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}
	// Check for vertical four in a rows, returning who won if one is found
	for (r=3; r<gameBoard.rows; r++){
		for(c=0; c<gameBoard.cols-3; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r-1][c+1] && gameBoard.board[r][c]==gameBoard.board[r-2][c+2] 
				&& gameBoard.board[r][c]==gameBoard.board[r-3][c+3] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}

	// If no four in a row is found, the game is ongoing, there is no winner
	return 0;
}

// Prints the end game screen
void ConnectFour::endgame(CFBoard gameBoard, int winner){
	// Print the board of the finished game and change text atrributes
	printHeader();
	gameBoard.print();	
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "\n\n";

	// Tell the players who won
	if(winner==3)
		cout << "                                      No moves left, it's a tie!\n";
	else
		cout << "                                  Congratulations player " << winner << ", you won!\n";

	// Exit to Connect Four menu
	ansi.textAttr("-bold");
	cout << "\n\n\n";
	cout << "                                 Press any key to return to the menu                                 " << endl;
	getch();
	ansi.textReset();
}

// Prints the header
void ConnectFour::printHeader(){
	ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+-------------------------------------------------------------------------------------------------+\n"
			"|                                                                                                 |\n" 
			"|          XXXXX  XXXXX  X   X  X   X  XXXXX  XXXXX  XXXXX    XXXXX  XXXXX  X   X  XXXXX          |\n" 
			"|          X      X   X  XX  X  XX  X  X      X        X      X      X   X  X   X  X   X          |\n" 
			"|          X      X   X  X X X  X X X  XXX    X        X      XXXX   X   X  X   X  XXXXX          |\n"
			"|          X      X   X  X  XX  X  XX  X      X        X      X      X   X  X   X  XXXX           |\n"
			"|          XXXXX  XXXXX  X   X  X   X  XXXXX  XXXXX    X      X      XXXXX  XXXXX  X   X          |\n"
			"|                                                                                                 |\n"
			"+-------------------------------------------------------------------------------------------------+\n" << endl;
	ansi.textReset();
}

// Prints the game rules
void ConnectFour::rules(){

}