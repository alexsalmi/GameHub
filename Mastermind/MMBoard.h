#ifndef MMBOARD_H
#define MMBOARD_H

#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <iostream>

const string colors[] = {"red", "blue", "green", "yellow", "white", "cyan", "none"};

class MMBoard{
public:
	// Constructor
	MMBoard(string sol[4]);
	// Prints the board to the cmd window
	void print();
	// Updates the board after a guess is made
	void update(string guess[4]);
	// Checks if the game is over or not
	bool isGameOver(string guess[4]);
	
	int currentGuess=0;

private:
	const static int guesses=7, length=4;
	string guessBoard[guesses][length];
	int feedback[guesses][length];
	string solution[length];

	// For ANSI escape commands
	dispANSI ansi;
};

#endif