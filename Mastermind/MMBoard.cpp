#include "MMBoard.h"

MMBoard::MMBoard(Colors sol[4]){
	for(int i=0; i<length; i++){
		solution[i] = sol[i];
		for(int j=0; j<guesses; j++){
			guessBoard[j][i] = None;
			feedback[j][i] = 0;
		}
	}
}

void MMBoard::print(){
	int i, j;
	cout << "_____________________\n";

	for(i=0; i<guesses; i++){
		cout << "| ";
		if(guessBoard[i][0]==None)
			cout << "        |         ";
		else{
			for(j=0; j<length; j++){
				switch(guessBoard[i][j]){
					case Red: ansi.textColor("red"); break;
					case Blue: ansi.textColor("blue"); break;
					case Green: ansi.textColor("green"); break;
					case Yellow: ansi.textColor("yellow"); break;
					case White: ansi.textColor("white"); break;
					case Cyan: ansi.textColor("cyan"); break; 
				}
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
	cout << "|_________|_________|\n" << endl;
}

bool MMBoard::update(Colors guess[4]){
	for(int i=0; i<length; i++){
		if(guess[i]==guessBoard[currentGuess][i])
			feedback[currentGuess][i] = 2;
		else{
			feedback[currentGuess][i] = 0;
			for(int j=0; j<length; j++){
				if(guess[i]==guessBoard[currentGuess][j]){
					feedback[currentGuess][i] = 1;
					break;
				}
			}
		}
	}

	currentGuess++;
	return 0;
}