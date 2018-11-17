#ifndef TTT_BOARD_H
#define TTT_BOARD_H

#include <iostream>
using namespace std;

// Constants for character key inputs
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// The tic tac toe game board
class TTTBoard{
public:
	// Constructor
	TTTBoard();

	// Prints the board to the cmd window
	void print();
	// Updates the board after a move is made or the cursor is movec
	void update(int moveKey, bool Xturn);
	// Place the CPU's move on the board
	void placeCPU(int pos);
	// Checks if position pos on the board is available
	bool isEmpty(int pos);
	
	// The board itself
	char board[9];

private:
	// Initializes the board
	void init();

	const int size=3;	// Size of the rows/columns 
	int cursorPos;		// Cursor position on the board
};

#endif