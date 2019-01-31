#ifndef HANGMAN_H
#define HANGMAN_H

#include "..\libs\Game.h"
#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <iostream>
#include <unordered_map>

using namespace std;

class Hangman : Game{
public:
	//Constructor
	Hangman();

	// Function for starting the game
	void start();

private:
	// Displays menu and takes input from user	
	int menu();
	// Main game loop 
	void play();
	// Displays post game screen
	void endgame(bool didGuess);
	// Prints the hanged man
	void printMan();
	// Prints memory header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	int limbsRemain = 6, lettersToGuess; 		// To keep track of limbs and letters in the word/phrase
	std::string legalChars = "abcdefghijklmnopqrstuvwxyz";	// Alphabet
	unordered_map<char, bool> charPool;			// To keep track of which letters have been guessed
	string word;								// For the inputted word/phrase from Player 1

	// For ansi escape commands
	dispANSI ansi;
};

#endif