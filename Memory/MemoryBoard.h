#ifndef MEMORYBOARD_H
#define MEMORYBOARD_H

#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <iostream>
#include <unordered_map>
#include "../libs/dispANSI.h"

using namespace std;

// Constants for character key inputs
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz~@$%&+?!#ÅÄÖåäö";
const int NUMSYMBOLS = 67;

enum Choice {first, second, waitingSuccess, waitingFail};

class MemoryBoard{
public:
	MemoryBoard();
	MemoryBoard(int r, int c);

	void init();

	// Prints the board to the cmd window
	void print();
	// Updates the board after a move is made or the cursor is moved
	void update(int moveKey);
	// Decides wether a move is a match and resets the board if not
	void makeMove();

	std::vector<std::vector<char>> board;
	std::vector<std::vector<bool>> showBoard, tempBoard;
	Choice choice = first;	// Choosing the first or second tile in a pair
	int pairsLeft = 0; // Number of pairs of symbols that still need to be matched

private:	
	int rows;		// Size of the board
	int cols;
	int cursX;		// Current x position of cursor
	int cursY;		// Current y position of cursor
	char firstChoice;
	bool didMatch;
	unordered_map<char, bool> symbolsUsed;


	dispANSI ansi;
};

#endif