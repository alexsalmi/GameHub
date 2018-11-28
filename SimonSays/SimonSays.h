#ifndef SIMONSAYS_H
#define SIMONSAYS_H

#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <cstdlib> 				// Used for rng 
#include <ctime>				// Used for setting seeds in rng
#include <fstream>				// Used for reading/writing to high score file
#include <iostream>
#include <sstream>				// Used for reading/writing to high score file
#include <string>
#include <vector>
#include <windows.h>			// Used for Sleep()

// Constants for character key inputs
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

enum Move {moveup, movedown, moveleft, moveright, movenone, moveall}; // Used to keep track of the moves to be played

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
	// Updates the high score file with a new score
	void updateHighScores(string name);
	// Prints all the high scores
	void printHighScores();
	// Prints tic tac toe header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	dispANSI ansi;						// For ansi excape commands
	std::vector<Move> moves;			// To keep track of the order of moves simon plays
	int score;							// To keep track of the score
	ifstream inFile;					// To read from the high score file
	ofstream outFile;					// To write to the high score file
	string HSFile = "./SimonSays/SimonSaysHighScores.txt";		// High score file
};

#endif