#ifndef HANGMAN_H
#define HANGMAN_H

#include "..\libs\dispANSI.h"
#include <conio.h>				// Used for getch() (reading character key inputs)
#include <iostream>
#include <unordered_map>

using namespace std;

class Hangman{
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
	// Prints the hanged man
	void printMan();
	// Displays post game screen
	void endgame(bool didGuess);
	// Prints memory header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();

	int limbsRemain = 6, lettersToGuess;
	std::string legalChars = "abcdefghijklmnopqrstuvwxyz";
	unordered_map<char, bool> charPool;
	string word;
	dispANSI ansi;
};

#endif