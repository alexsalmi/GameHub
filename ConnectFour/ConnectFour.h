#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "CFBoard.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
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
	void play();
	// Displays post game screen
	void endgame();
	// Prints memory header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	dispANSI ansi;						// For ansi excape commands
};

#endif