#include "ConnectFour.h"

ConnectFour::ConnectFour(){};

void ConnectFour::start(){
	int menuChoice;	
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(); break;
			case 2: play(); break;
			case 3: rules(); break;
			default: break;
		}
	}while(menuChoice!=0);
}

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

		cout << "                             (1) Play Connect Four vs. the CPU    (1 Player)                       \n"
				"                             (2) Play Connect Four vs. a friend   (2 Player)                       \n" << endl;
		
		cout <<	"                             (3) View game rules and controls\n" << endl;

		cout << "                             (0) Return to GameHub							                         " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice<=3 && menuChoice>=0){
			return menuChoice;
		}
	}
}

void ConnectFour::play(){
	CFBoard gameBoard;
	int moveKey;
	playerTurn = 1;

	while(true){
		printHeader();
		gameBoard.print();
		ansi.textColor("green");
		ansi.textAttr("bold");
		cout << "\n\n\n";

		ansi.textAttr("-bold");
		cout << "                  [Arrow Keys] - Move     [Spacebar] - Choose tile     [q] - Quit                  " << endl;

		ansi.textReset();

		// Get character key input from user and update the gameboard accordingly
		moveKey = getch();		
		if(moveKey==224)
			moveKey = getch();
		if(gameBoard.update(moveKey, playerTurn)){
			int winner = isGameOver(gameBoard);
			if(winner!=0){
				endgame(gameBoard, winner);
				return;
			}
			playerTurn = ((playerTurn)%2)+1;
		}

		if(moveKey=='q')
			return;
	}
}

int ConnectFour::isGameOver(CFBoard gameBoard){
	int r, c;
	for (r=0; r<gameBoard.rows; r++){
		for(c=0; c<gameBoard.cols-3; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r][c+1] && gameBoard.board[r][c]==gameBoard.board[r][c+2] 
				&& gameBoard.board[r][c]==gameBoard.board[r][c+3] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}
	for (r=0; r<gameBoard.rows-3; r++){
		for(c=0; c<gameBoard.cols; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r+1][c] && gameBoard.board[r][c]==gameBoard.board[r+2][c] 
				&& gameBoard.board[r][c]==gameBoard.board[r+3][c] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}
	for (r=0; r<gameBoard.rows-3; r++){
		for(c=0; c<gameBoard.cols-3; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r+1][c+1] && gameBoard.board[r][c]==gameBoard.board[r+2][c+2] 
				&& gameBoard.board[r][c]==gameBoard.board[r+3][c+3] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}
	for (r=3; r<gameBoard.rows; r++){
		for(c=0; c<gameBoard.cols-3; c++){
			if(gameBoard.board[r][c]==gameBoard.board[r-1][c+1] && gameBoard.board[r][c]==gameBoard.board[r-2][c+2] 
				&& gameBoard.board[r][c]==gameBoard.board[r-3][c+3] && gameBoard.board[r][c]!=0)
				return gameBoard.board[r][c];
		}
	}

	return 0;
}

void ConnectFour::endgame(CFBoard gameBoard, int winner){
	// Print the board of the finished game and change text atrributes
	printHeader();
	gameBoard.print();	
	ansi.textColor("green");
	cout << "\n\n\n";

	cout << "                                  Congratulations player " << winner << ", you won!\n";

	// Exit to tic tac toe menu
	cout << "\n\n\n";
	cout << "                                 Press any key to return to the menu                                 " << endl;
	getch();
	ansi.textReset();
}

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

void ConnectFour::rules(){

}