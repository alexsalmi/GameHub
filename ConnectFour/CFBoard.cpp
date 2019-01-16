#include "CFBoard.h"

// Constructor
CFBoard::CFBoard(){
	// Sets the board size to the default value
	rows = 6;
	cols = 7;

	// Initializes the board values
	init();
}

CFBoard::CFBoard(int r, int c){
	// Sets the board size to the default value
	rows = r;
	cols = c;

	// Initializes the board values
	init();
}

void CFBoard::init(){
	int r, c;

	// fills the board with zeros (empty spaces)
	cursor = cols/2;
	std::vector<int> vec;
	for(r=0; r<rows; r++){
		vec = {};
		for(c=0; c<cols; c++)
			vec.push_back(0);
		board.push_back(vec);
	}
}

// Updates the board after a move is made or the cursor is moved
bool CFBoard::update(int moveKey, int playerTurn){
	// Updates the game based on the entered key
	switch(moveKey){
		// If the left arrow is pressed and the cursor can move left, move it left
		case KEY_LEFT:
			if(cursor>0)
				cursor--;
			break;
		// If the right arrow is pressed and the cursor can move right, move it right
		case KEY_RIGHT:
			if(cursor<cols-1)
				cursor++;
			break;
		// If the spacebar is pressed, place the piece at the current cursor location, if possible
		case ' ':
			return makeMove(playerTurn);
		default:break;
	}
	// If makeMove was not called or returned false, no piece has been placed, so return false
	return false;
}

// Decides wether a move is a match and resets the board if not
bool CFBoard::makeMove(int playerTurn){
	// The the top row of the curent column is free, the move is possible
	if(board[0][cursor]==0){
		int i;
		// Drop the piece down as far as it'll go, landing on top of the highest current piece in this column
		for(i=0; i<rows; i++){
			if(board[i][cursor]!=0)
				break;
		}
		board[i-1][cursor] = playerTurn;	// Place the current player's piece
		return true;						// Return true indicating that a piece was placed
	}
	// No piece has been placed, so return false
	return false;
}

// Prints the game board to the cmd window
void CFBoard::print(){
	ansi.textColor("green");
	ansi.textAttr("bold");
	int i, r, c; 
	// Print the cursor above the board
	cout << "                                    ";
	for(i=0; i<cols; i++){
		if(cursor==i)
			cout << " v  ";		// Cursor itself
		else
			cout << "    ";
	}
	cout << "\n";

	// Print the top layer of the board
	cout << "                                   ";
	for(i=0; i<(cols*4)+1; i++)
		cout << "_";
	cout << "\n";

	// Print all of the spaces on the board, changing the color according to the player's pieced on the board
	for(r=0; r<rows; r++){
		cout << "                                   ";
		cout << "|";
		for(c=0; c<cols; c++){
			switch(board[r][c]){
				case 0: ansi.textColor("green"); break;		// Empty space
				case 1: ansi.textColor("blue"); break;		// Player 1's piece
				case 2: ansi.textColor("red"); break;		// Player 2's piece
			}
			cout << " O ";
			ansi.textColor("green");
			cout << "|";
		}
		cout << "\n                                   ";
		if(r!=(rows-1)){
			cout << "|";
			for(c=0; c<cols; c++)
				cout << "   |";
			cout << "\n";
		}
	}
	cout << "|";
	for(i=0; i<cols; i++)
		cout << "___|";
	cout << "\n";
	ansi.textReset();
}