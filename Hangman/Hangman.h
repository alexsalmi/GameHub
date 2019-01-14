#ifndef HANGMAN_H
#define HANGMAN_H

#include <conio.h>				// Used for getch() (reading character key inputs)
#include <iostream>

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
	// Displays post game screen
	void endgame();
	// Prints memory header to cmd window
	void printHeader();	
	// Displays the rules of the game
	void rules();
};

#endif