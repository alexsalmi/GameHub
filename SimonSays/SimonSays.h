#ifndef SIMONSAYS_H
#define SIMONSAYS_H

#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <iostream>
#include <windows.h>			// Used for Sleep()

using namespace std;

enum move {up, down, left, right}; // Used to keep track of the moves to be played

class SimonSays{
public:
	// Constructor
	SimonSays();

	// Function for starting the game
	void start();
private:
	// Displays menu and takes input from user	
	int menu();
	// Main game loop 
	void play();
	// Prints tic tac toe header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	dispANSI ansi;

};

#endif