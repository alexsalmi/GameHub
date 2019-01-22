#include "MMBoard.h"

MMBoard::MMBoard(string sol[4]){
	for(int i=0; i<length; i++){
		solution[i] = sol[i];
		for(int j=0; j<guesses; j++){
			guessBoard[j][i] = "none";
			feedback[j][i] = 0;
		}
	}
}

void MMBoard::print(){
	int i, j;
	cout << "                                       _____________________                                       \n";

	for(i=0; i<guesses; i++){
		cout << "                                       |         |         |\n"
				"                                       | ";
		if(guessBoard[i][0]=="none")
			cout << "        |         ";
		else{
			for(j=0; j<length; j++){
				ansi.textColor(guessBoard[i][j]);
				cout << "O ";
			}
			ansi.textColor("green");
			cout << "| ";
			for(j=0; j<length; j++){
				switch(feedback[i][j]){
					case 0: cout << "X "; break;
					case 1: cout << "/ "; break;
					case 2: cout << "O "; break;
				}
			}
			cout << "| ";
		}
		cout << "|\n";
	}
	cout << "                                       |_________|_________|                                       \n" << endl;
}

void MMBoard::update(string guess[4]){
	for(int i=0; i<length; i++){
		guessBoard[currentGuess][i] = guess[i];
		if(guess[i]==solution[i])
			feedback[currentGuess][i] = 2;
		else{
			feedback[currentGuess][i] = 0;
			for(int j=0; j<length; j++){
				if(guess[i]==solution[j]){
					feedback[currentGuess][i] = 1;
					break;
				}
			}
		}
	}

	currentGuess++;
}

// Checks if the game is over or not
bool MMBoard::isGameOver(string guess[4]){
	for(int i=0; i<length; i++){
		if(guess[i]!=solution[i])
			return false;
	}
	return true;
}