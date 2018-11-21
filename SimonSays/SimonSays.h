#ifndef SIMONSAYS_H
#define SIMONSAYS_H

#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <iostream>
#include <vector>
#include <windows.h>			// Used for Sleep()

// Constants for character key inputs
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

enum Move {moveup, movedown, moveleft, moveright, movenone}; // Used to keep track of the moves to be played

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
	// Prints the images of the keys to the cmd window
	void printKeys(Move dir, bool gameOver);
	// Prints the post game screen to the cmd window
	void endgame();
	// Prints tic tac toe header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	dispANSI ansi;
	std::vector<Move> moves;
	int score;
};

#endif