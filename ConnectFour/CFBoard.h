#ifndef CFBOARD_H
#define CFBOARD_H

#include <conio.h>
#include <iostream>
#include "../libs/dispANSI.h"

using namespace std;

// Constants for character key inputs
#define KEY_LEFT 75
#define KEY_RIGHT 77

class CFBoard{
public: 
	CFBoard();
	CFBoard(int r, int c);
 
	void init();

	// Prints the board to the cmd window
	void print();
	// Updates the board after a move is made or the cursor is moved
	bool update(int moveKey, int playerTurn);
	// Decides wether a move is a match and resets the board if not
	bool makeMove(int playerTurn);

	int rows;		// Size of the board
	int cols;
	std::vector<std::vector<int>> board;	// board itself

private:
	int cursor;		// Cursor position

	// For ansi escape commands
	dispANSI ansi;
};

#endif