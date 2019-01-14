#include "Hangman.h"

//Constructor
Hangman::Hangman(){
	for(char c : legalChars)
		charPool[c] = true;
}

// Begin the Hangman application
void Hangman::start(){
	int menuChoice;

	// Show the menu screen until user quits out
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(); break;				// Play Hangman
			case 2: rules(); break;				// Rules of Hangman
			default: break;
		}
	}while(menuChoice!=0);
}

int Hangman::menu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << endl;
		cout << "                                       Welcome to Hangman!                                         \n" 
				"                             Please select an option from the menu below:                          \n" << endl << endl;

		cout << "                             (1) Play Hangman                                                      \n" << endl;
		
		cout << "                             (2) View game rules and controls\n" << endl;

		cout << "                             (0) Return to GameHub							                         " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice<=2 && menuChoice>=0)
			return menuChoice;
	}
}

void Hangman::play(){
	char guess;
	bool correct;
	std::string spaces;
	limbsRemain = 6;
	for(char c : legalChars)
		charPool[c] = true;

	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");

	cout << "               Player 1, please enter a word or phrase for Player 2 to try to guess:               \n"
			"               ";
	cin >> word;
	// Error check for invalid input
	if(cin.fail()){
		cin.clear();
    	cin.ignore();
	}

	lettersToGuess = word.length();
	for(char c: word){
		if(c==' ' || c==',' || c=='.' || c=='!' || c=='?' || c=='-')
			lettersToGuess--;		
	}

	while(limbsRemain>0){
		printHeader();
		ansi.textColor("green");
		ansi.textAttr("bold");

		printMan();

		spaces = "";
		for(int i=0; i<(50-(word.length()/2)); i++){
			spaces += " ";
		}
		cout << spaces;
		for(char c: word){
			if(c==' ' || c==',' || c=='.' || c=='!' || c=='?' || c=='-')
				cout << c;
			else if(charPool[c])
				cout << '#';
			else
				cout << c;
		}
		cout << "\n\n";

		cout << "                        ";
		for(char c : legalChars){
			if(!charPool[c])
				ansi.textAttr("-bold");
			cout << c << " ";
			ansi.textAttr("bold");
		}

		cout << "\n\n";

		cout << "                           Player 1, please choose a letter to guess: ";
		cin >> guess;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
	    	cin.ignore();
		}
		if(charPool[guess]){
			charPool[guess] = false;

			correct = false;
			for(char c: word){
				if(c==guess){
					correct = true;
					lettersToGuess--;
				}
			}

			if(!correct)
				limbsRemain--;

			if(limbsRemain==0){
				endgame(false);
				return;
			}
			else if(lettersToGuess==0){
				endgame(true);
				return;
			}
		}
	}
}

void Hangman::endgame(bool didGuess){
	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");

	printMan();

	if(didGuess)
		cout << "                                  Congratulations player 2, you won!\n\n";
	else
		cout << "                                  Congratulations player 1, you won!\n\n";

	cout << "                                Press any key to return to the menu                                \n" << endl;
	getch();
	ansi.textReset();
}

void Hangman::printMan(){
	cout << "                                        XXXXXXXXXX           \n"
			"                                        X        X           \n";
	if(limbsRemain<6){
		cout << "                                        X      XXXXX         \n"
				"                                        X     X     X        \n"
		        "                                        X     X     X        \n"
		        "                                        X      XXXXX         \n";
	}
	else{
		cout << "                                        X                    \n"
				"                                        X                    \n"
		        "                                        X                    \n"
		        "                                        X                    \n";

	}
	if(limbsRemain<3){
		cout << "                                        X        X           \n"
		        "                                        X       XXX          \n"
		        "                                        X      X X X         \n"
		        "                                        X     X  X  X        \n"
		        "                                        X    X   X   X       \n";
	}
	else if(limbsRemain<4){
		cout << "                                        X        X           \n"
		        "                                        X       XX           \n"
		        "                                        X      X X           \n"
		        "                                        X     X  X           \n"
		        "                                        X    X   X           \n";
	}
	else if(limbsRemain<5){
		cout << "                                        X        X           \n"
		        "                                        X        X           \n"
		        "                                        X        X           \n"
		        "                                        X        X           \n"
		        "                                        X        X           \n";
	}
	else{
		cout << "                                        X                    \n"
		        "                                        X                    \n"
		        "                                        X                    \n"
		        "                                        X                    \n"
		        "                                        X                    \n";
	}
	if(limbsRemain<1){
		cout << "                                        X        X           \n"
		        "                                        X       X X          \n"
		        "                                        X      X   X         \n"
		        "                                        X    XX     XX       \n"
		        "                                      XXXXX                  \n" << endl;
	}
	else if(limbsRemain<2){
		cout << "                                        X        X           \n"
		        "                                        X       X            \n"
		        "                                        X      X             \n"
		        "                                        X    XX              \n"
		        "                                      XXXXX                  \n" << endl;
	}
	else{
		cout << "                                        X                    \n"
		        "                                        X                    \n"
		        "                                        X                    \n"
		        "                                        X                    \n"
		        "                                      XXXXX                  \n" << endl;
	}  
}

// Prints the header
void Hangman::printHeader(){
    ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+-------------------------------------------------------------------------------------------------+\n"
			"|                                                                                                 |\n" 
			"|                         X   X  XXXXX  X   X  XXXXX  XXXXX  XXXXX  X   X                         |\n" 
			"|                         X   X  X   X  XX  X  X      X X X  X   X  XX  X                         |\n" 
			"|                         XXXXX  XXXXX  X X X  X  XX  X X X  XXXXX  X X X                         |\n"
			"|                         X   X  X   X  X  XX  X   X  X X X  X   X  X  XX                         |\n"
			"|                         X   X  X   X  X   X  XXXXX  X X X  X   X  X   X                         |\n"
			"|                                                                                                 |\n"
			"+-------------------------------------------------------------------------------------------------+\n" << endl;
	ansi.textReset();
}

// Prints the game rules
void Hangman::rules(){
	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "                                              RULES:                                               \n" << endl;
	ansi.textAttr("-bold");
	
	/*cout << "              Simon Says is a game where you will be shown a series of button presses              \n" 
			"              which you must then repeat back. The buttons used will be the four                   \n"
			"              arrow keys, presented to you in a random order.                                      \n"
			"              You must repeat back the same arrow keys in the exact same order they                \n"
			"              were presented to you.\n"
			"              Every turn, if you correctly enter the keys in the correct order, the                \n"
			"              displayed keys will all flash to signify that you repeated the sequence              \n"
			"              correctly.\n"
			"              When you fail to press the keys in the correct order, the game will be               \n"
			"              over, and your final score will be the number of turns you survived.                 \n"<< endl;
	*/
	ansi.textAttr("bold");
	cout << "                                            CONTROLS:                                              \n" << endl;
	ansi.textAttr("-bold");
	/*
	cout << "                                 [Arrow keys] - Copy Simon's moves                                 \n" << endl;

	ansi.textAttr("bold");
    cout << "\n\n\n";
    */
	cout << "                                Press any key to return to the menu                                \n" << endl;
	ansi.textAttr("-bold");
	getch();
	ansi.textReset();
}