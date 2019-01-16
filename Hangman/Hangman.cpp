#include "Hangman.h"

//Constructor
Hangman::Hangman(){
	// Initializes each char in the pool as true, since they have not been guessed yet
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

// Displays menu and takes input from user	
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

// Main game loop 
void Hangman::play(){
	char guess;
	bool correct;
	std::string spaces;
	limbsRemain = 6;
	// Reset the charPool before the game
	for(char c : legalChars)
		charPool[c] = true;

	// Print the screen for Player 1 to enter the word/phrase to be guessed
	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "               Player 1, please enter a word or phrase for Player 2 to try to guess:               \n"
			"               ";
	// Get the word or phrase. Using getline to include spaces
	std::getline(std::cin >> std::ws, word);
	// Error check for invalid input
	if(cin.fail()){
		cin.clear();
    	cin.ignore();
	}

	// Keep track of how many letters need to be guessed
	lettersToGuess = word.length();
	for(char c: word){
		if(c==' ' || c==',' || c=='.' || c=='!' || c=='?' || c=='-' || c=='\'')
			lettersToGuess--;		
	}

	// Main game loop
	while(limbsRemain>0){
		printHeader();
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Prints the hanged man to the cmd window
		printMan();

		// Adjust the nember of spaced in front of the word so that the word is centered
		spaces = "";
		for(int i=0; i<(50-(word.length()/2)); i++)
			spaces += " ";

		// Print the word, showing only the letters that have been guessed, and any punctuation
		cout << spaces;
		for(char c: word){
			if(c==' ' || c==',' || c=='.' || c=='!' || c=='?' || c=='-')
				cout << c;
			// Checking for capital letters
			else if((c-'A')>=0 && (c-'A')<26){
				// If the letter is in the charPool, it has not been guessed, so don't show it
				if(charPool[c+32])
					cout << '#';
				else
					cout << c;
			}
			// If the letter is in the charPool, it has not been guessed, so don't show it
			else if(charPool[c])
				cout << '#';
			else
				cout << c;
		}
		cout << "\n\n";

		// Print all of the letters, unbolding the letters that have already been guessed
		cout << "                        ";
		for(char c : legalChars){
			if(!charPool[c])
				ansi.textAttr("-bold");
			cout << c << " ";
			ansi.textAttr("bold");
		}

		cout << "\n\n";

		// Get the guessed letter from Player 2
		cout << "                           Player 1, please choose a letter to guess: ";
		cin >> guess;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
	    	cin.ignore();
		}
		// Check for capital letter, change them to lower case
		if((guess-'A')>=0 && (guess-'A')<26)
			guess = guess + 32;
		// If the letter is in the charPool, it has not been guessed, so we can continue
		if(charPool[guess]){
			// Mark the letter as being guessed
			charPool[guess] = false;

			// Check if the letter is in the word/phrase. If it is, update lettersToGuess for each occurance
			correct = false;
			for(char c: word){
				if(c==guess || (c+32)==guess){
					correct = true;
					lettersToGuess--;
				}
			}

			// If it was an incorrect guess, hang another limb
			if(!correct)
				limbsRemain--;

			// If there are no limbs left, the game is over, show endgame screen
			if(limbsRemain==0){
				endgame(false);
				return;
			}
			// If the word has been fully guessed, the game is over, show endgame screen
			else if(lettersToGuess==0){
				endgame(true);
				return;
			}
		}
	}
}

// Displays post game screen
void Hangman::endgame(bool didGuess){
	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");

	printMan();

	// Tell the players who won
	if(didGuess)
		cout << "                                 Congratulations player 2, you won!\n\n";
	else
		cout << "                                 Congratulations player 1, you won!\n\n";

	// Prompt user to return to the menu
	cout << "                                Press any key to return to the menu                                \n" << endl;
	getch();
	ansi.textReset();
}

// Prints the figure of the hanged man
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