#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <iostream>

using namespace std;

enum Colors {Red, Blue, Green, Yellow, White, Cyan};
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

	Colors solution[4];
	Colors guess[4];
	int solLength = 4;
	bool multiplayer;
	dispANSI ansi;
};

#endif