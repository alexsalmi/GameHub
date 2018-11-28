#include "TTTBoard.h"

// Constructor
TTTBoard::TTTBoard(){
	init();
}

// Initialize the board
void TTTBoard::init(){
	// All spaces should be empty
	for(int i=0; i<size*size; i++){
		board[i] = ' ';
	}
	// Place the cursor in the middle of the board
	board[(size*size)/2] = '.';
	cursorPos = size*size/2;
}

// Update the board when a move is made or the cursor is moved, returns true when a move was made
bool TTTBoard::update(int moveKey, bool Xturn){
	int newPos = cursorPos;

	switch(moveKey){
		// Move curser up on board if possible
		case KEY_UP:
			if(cursorPos>2)
				newPos = cursorPos-3;
			break;
		// Move curser down on board if possible
		case KEY_DOWN:
			if(cursorPos<6)
				newPos = cursorPos+3;
			break;
		// Move curser to the right on board if possible
		case KEY_RIGHT:
			if((cursorPos+1)%size!=0)
				newPos = cursorPos+1;
			break;
		// Move curser to the left on board if possible
		case KEY_LEFT:
			if((cursorPos+1)%size!=1)
				newPos = cursorPos-1;
			break;
		// Places the piece on the board
		case ' ':
			// Checks to see that the board is not occupied
			if(board[cursorPos]=='.'){
				if(Xturn)
					board[cursorPos] = 'X';
				else
					board[cursorPos] = 'O';
				return true;
			}
			break;
		default:break;
	}
	// Update the cursor's previous and current spaces on the board 
	if(newPos!=cursorPos){
		switch(board[cursorPos]){
			case '.': board[cursorPos] = ' '; break;
			case 'x': board[cursorPos] = 'X'; break;
			case 'o': board[cursorPos] = 'O'; break;
			default: break;
		}
		switch(board[newPos]){
			case ' ': board[newPos] = '.'; break;
			case 'X': board[newPos] = 'x'; break;
			case 'O': board[newPos] = 'o'; break;
			default: break;
		}
		cursorPos = newPos;
	}
	return false;
}

// Checks to see if position pos on the board is available
bool TTTBoard::isEmpty(int pos){
	return board[pos] == ' ';
}

// Places the CPU's move on the board
void TTTBoard::placeCPU(int pos){
	if(pos>=0 && pos<size*size && isEmpty(pos))
		board[pos] = 'O';
}

// Prints the board to the cmd window
void TTTBoard::print(){
	ansi.textAttr("bold");
	ansi.textColor("green");
	cout << endl;
	cout << "                                            |         |                                            " << endl;
	cout << "                                       " << board[0] << "    |    " << board[1] << "    |    " << board[2] << endl;
	cout << "                                            |         |                              " << endl;
	for(int i=1; i<size; i++){
		cout << "                                   _____________________________                                   " << endl;
		cout << "                                            |         |                              " << endl;
		cout << "                                       " << board[0+i*size] << "    |    " << board[1+i*size] << "    |    " << board[2+i*size] << endl;
		cout << "                                            |         |                              " << endl;
	}
	ansi.textReset();
}