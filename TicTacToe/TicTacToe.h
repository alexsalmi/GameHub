#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "..\libs\Game.h"
#include "TTTBoard.h"			// Gameboard
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <iostream>
#include <windows.h>			// Used for Sleep()

using namespace std;

enum Winner {X, O, CPU, Player, Draw, NA};	// Used for determining who won the game
enum Difficulty {easy, medium, hard, multiplayer}; // Used to keep track of the difficulty of the CPU

class TicTacToe : Game{
public:
	// Constructor
	TicTacToe();			

	// Function for starting the game
	void start();			 

private:
	// Displays menu and takes input from user	
	int menu();
	// Main game loop 
	void play(bool multiplayer, Difficulty diff);
	// Plays the CPU's turn of the game
	int cpuTurn(Difficulty diff, TTTBoard gameBoard);
	// Find potential winning moves, returns the index
	int winningMove(char character, TTTBoard gameBoard);
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
	dispANSI ansi;
};

#endif