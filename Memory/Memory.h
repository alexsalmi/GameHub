#ifndef MEMORY_H
#define MEMORY_H

#include "..\libs\dispANSI.h"
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <iostream>

using namespace std;

class Memory{
public:
	// Constructor
	Memory();

	// Function for starting the game
	void start();
private:
	// Displays menu and takes input from user	
	int menu();
	// Main game loop 
	void play();
	// Prints memory header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	dispANSI ansi;						// For ansi excape commands
};


#endif