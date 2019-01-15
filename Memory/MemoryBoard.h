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

// The pool of chars that can be used on the board
const string SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz~@$%&+?!#ÅÄÖåäö";
const int NUMSYMBOLS = 67;

// Game state
enum Choice {first, second, waitingSuccess, waitingFail};

class MemoryBoard{
public:
	// Constructor
	MemoryBoard();
	MemoryBoard(int r, int c);

	void init();

	// Prints the board to the cmd window
	void print();
	// Updates the board after a move is made or the cursor is moved
	void update(int moveKey);
	// Decides wether a move is a match and resets the board if not
	void makeMove();

	std::vector<std::vector<char>> board; // Game board
	std::vector<std::vector<bool>> showBoard, tempBoard; // Bool vector to indicate if each tile is currently visible or not
	Choice choice = first;	// Choosing the first or second tile in a pair
	int pairsLeft = 0; // Number of pairs of symbols that still need to be matched

private:	
	int rows;			// Size of the board
	int cols;
	int cursX;			// Current x position of cursor
	int cursY;			// Current y position of cursor
	char firstChoice;	// To save the first choice of each guess, to compare with the second choice
	bool didMatch;		// A bool to keep track of if a guess was a match
	unordered_map<char, bool> symbolsUsed;	// Map to keep track of which symbols are placed on the board

	dispANSI ansi;		// For ansi excape commands
};

#endif