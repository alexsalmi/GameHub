#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "TTTBoard.h"			// Gameboard
#include <iostream>
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <windows.h>			// Used for Sleep()
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng

using namespace std;

enum Winner {X, O, CPU, Player, Draw, NA};	// Used for determining who won the game

class TicTacToe{
public:
	// Constructor
	TicTacToe();			

	// Function for starting the game
	void start();			 

private:
	// Displays menu and takes input from user	
	int menu();
	// Main game loop 
	void play(bool multiplayer);
	// Checks if the game is over or not
	Winner isGameOver(TTTBoard gameBoard, bool multiplayer);
	// Displays post game screen
	void endgame(Winner winner, TTTBoard gameBoard);
	// Prints tic tac toe header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	bool Xturn;				// keep track of who's turn it is
	int movesRemaining;		// keep track of how many spaces are left on board
	const int size=3;		// number of rows/cols on board
};

#endif