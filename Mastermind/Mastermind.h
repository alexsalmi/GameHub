#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "MMBoard.h"
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng

using namespace std;

const int NUM_OF_COLORS = 6;

class Mastermind{
public:
	// Constructor
	Mastermind();

	// Function for starting the game
	void start();

private:
	// Displays menu and takes input from user	
	int menu();
	// Main game loop 
	void play(bool mult);
	// Displays post game screen
	void endgame();
	// Prints mastermind header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	const static int solLength = 4;
	Colors solution[solLength];
	Colors guess[solLength];
	int turnsLeft = 7;
	bool multiplayer;

	// For ANSI escape commands
	dispANSI ansi;
};

#endif