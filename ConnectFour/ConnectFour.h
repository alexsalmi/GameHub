#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "..\libs\Game.h"
#include "CFBoard.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <iostream>

using namespace std;

class ConnectFour : Game{
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
	// Checks if the game is over or not
	int isGameOver(CFBoard gameBoard);
	// Displays post game screen
	void endgame(CFBoard gameBoard, int winner);
	// Prints memory header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	int playerTurn;		// To keep track of who's turn it is
	int movesLeft;		// Keeps track of how many spaces are available on the board

	// For ansi excape commands
	dispANSI ansi;				
};

#endif