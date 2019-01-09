#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <conio.h>				// Used for getch() (reading character key inputs)
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <iostream>

using namespace std;

class ConnectFour{
public:
	//Constructor
	ConnectFour();

	// Function for starting the game
	void start();

private:
	// Displays menu and takes input from user	
	int menu();
	// Main game loop 
	void play(Difficult diff);
	// Displays post game screen
	void endgame(MemoryBoard gameBoard);
	// Prints memory header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	dispANSI ansi;						// For ansi excape commands
}

#endif