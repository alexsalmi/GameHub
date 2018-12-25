#ifndef MEMORYBOARD_H
#define MEMORYBOARD_H

#include <iostream>
#include <unordered_map>
#include "../libs/dispANSI.h"

using namespace std;

// Constants for character key inputs
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz~@$%&+?!¤#ÅÄÖåäö";
const int NUMSYMBOLS = 68;

class MemoryBoard{
public:
	MemoryBoard();
	MemoryBoard(int r, int c);

	void init();

	// Prints the board to the cmd window
	void print();
	// Updates the board after a move is made or the cursor is movec
	bool update(int moveKey, bool Xturn);

	std::vector<std::vector<char>> board;

private:	
	int rows;		// Size of the board
	int cols;
	int cursX;		// Current x position of cursor
	int cursY;		// Current y position of cursor
	unordered_map<char, bool> symbolsUsed;
	

	dispANSI ansi;
};

#endif