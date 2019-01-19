#ifndef MMBOARD_H
#define MMBOARD_H

#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <iostream>

enum Colors {Red, Blue, Green, Yellow, White, Cyan, None};

class MMBoard{
public:
	// Constructor
	MMBoard(Colors sol[4]);
	// Prints the board to the cmd window
	void print();
	// Updates the board after a guess is made
	bool update(Colors guess[4]);

private:
	const static int guesses=7, length=4;
	int guessBoard[guesses][length];
	int feedback[guesses][length];
	int currentGuess=1;
	Colors solution[length];

	// For ANSI escape commands
	dispANSI ansi;
};

#endif