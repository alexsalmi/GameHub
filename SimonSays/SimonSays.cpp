#include "SimonSays.h"

//Constructor
SimonSays::SimonSays(){}

// Begin the SimonSays application
void SimonSays::start(){
	int menuChoice;

	// Show the menu screen until user quits out
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(); break;			// Play Simon Says
			case 2: rules(); break;			// Rules
			default: break;
		}
	}while(menuChoice!=0);
}

int SimonSays::menu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << "                         Welcome to Simon Says!                        \n" 
				"               Please select an option from the menu below:            \n" << endl;

		cout << "               (1) Play Simon Says                                     \n" << endl;
		
		cout << "               (2) View high scores 				 			        \n"
				"               (3) View game rules and controls 				        \n" << endl;

		cout << "               (0) Return to GameHub							        " << endl;
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

void SimonSays::play(){
	bool gameOver = false;			// keep track of if the game is over
	int moveKey;
	moves = {};
	score = 0;

	srand((unsigned)time(0));
	while(!gameOver){
		printKeys(movenone, gameOver);

		Sleep(500);

		int pickMove = rand()%(4);
		switch(pickMove){
			case 0: moves.push_back(moveup); break;
			case 1: moves.push_back(movedown); break;
			case 2: moves.push_back(moveleft); break;
			case 3: moves.push_back(moveright); break;
		}

		for(Move& m : moves){
			printKeys(m, gameOver);
			Sleep(500);

			printKeys(movenone, gameOver);
			Sleep(100);
		}

		printKeys(movenone, gameOver);		

		for(Move& m : moves){
			moveKey = getch();
			if(moveKey == 224)
				moveKey = getch();
			
			if((moveKey == KEY_UP && m == moveup)||
				(moveKey == KEY_DOWN && m == movedown)||
				(moveKey == KEY_LEFT && m == moveleft)||
				(moveKey == KEY_RIGHT && m == moveright)){
				printKeys(m, gameOver);
			}
			else{
				gameOver = true;
				printKeys(movenone, gameOver);
				//updateHighScores(score, "alex");
				endgame();
				break;
			}
		}
		if(!gameOver){
			score++;
			cout << "                       Nice! Simon is impressed.                        " << endl;

			Sleep(1000);
		}
	}
}

// Prints the images of the keys to the cmd window
void SimonSays::printKeys(Move dir, bool gameOver){
	printHeader(); 
	ansi.textColor("green");
	ansi.textAttr("bold");

	for(int i=0; i<3; i++){
		cout << "                               ";
		if(dir==moveup)
			ansi.textAttr("reverse");
		cout << "^^^^^^^\n";
		if(dir==moveup)
			ansi.textAttr("-reverse");
	}


	for(int i=0; i<3; i++){
		cout << "                        ";
		if(dir==moveleft)
			ansi.textAttr("reverse");
		cout << "<<<<<<<";
		if(dir==moveleft)
			ansi.textAttr("-reverse");

		cout << "       ";
		if(dir==moveright)
			ansi.textAttr("reverse");
		cout << ">>>>>>>" << endl;
		if(dir==moveright)
			ansi.textAttr("-reverse");
	}

	for(int i=0; i<3; i++){
		cout << "                               ";
		if(dir==movedown)
			ansi.textAttr("reverse");
		cout << "vvvvvvv\n";
		if(dir==movedown)
			ansi.textAttr("-reverse");
	}

	cout << endl << endl;

	if(!gameOver)
		cout << "                               Score: " << score << endl;
}

void SimonSays::endgame(){
	cout << "                    Sorry, wrong button. Game over!                      " << endl << endl;
	cout << "                            Final score: " << score << endl << endl;
	// Exit to Simon Says menu
	cout << "                  Press any key to return to the menu                    " << endl;
	updateHighScores("alex");
	int moveKey = getch();
	if(moveKey == 224)
		moveKey = getch();
	ansi.textReset();
}

// Updates the high score file with a new score
void SimonSays::updateHighScores(string name){
	vector<string> n;
	string in, numname;
	int num;
	bool recorded = false;
	inFile.open(HSFile);

	if(!inFile.is_open()){
		inFile.close();
		outFile.open(HSFile, ios::out | ios::trunc);
		outFile << name << " " << score;
		outFile.close();
	}
	else{
		while(getline(inFile, in)){
			istringstream iss(in);
			iss >> numname >> num;

			if(score>num && !recorded){
				n.push_back(name + " " + to_string(score));
				recorded = true;
			}
			n.push_back(in);
		}

		if(!recorded)
			n.push_back(name + " " + to_string(score));

		inFile.close();

		outFile.open(HSFile, ios::out | ios::trunc);

		if(outFile.is_open()){
			for(int i=0; i<n.size() || i<10; i++){
				outFile << n[i] << endl;
			}
		}
		else{
			cout << "outFile is not open" << endl;
		}

		outFile.close();
	}
}

// Prints all the high scores
void SimonSays::printHighScores(){

}

void SimonSays::printHeader(){
    ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+---------------------------------------------------------------------+\n"
			"|                                                                     |\n" 
			"|   XXXXX  XXXXX  XXXXX  XXXXX  X   X    XXXXX  XXXXX  X   X  XXXXX   |\n" 
			"|   X        X    X X X  X   X  XX  X    X      X   X  X   X  X       |\n" 
			"|   XXXXX    X    X X X  X   X  X X X    XXXXX  XXXXX  XXXXX  XXXXX   |\n"
			"|       X    X    X X X  X   X  X  XX        X  X   X    X        X   |\n"
			"|   XXXXX  XXXXX  X X X  XXXXX  X   X    XXXXX  X   X    X    XXXXX   |\n"
			"|                                                                     |\n"
			"+---------------------------------------------------------------------+\n" << endl;
	ansi.textReset();
}

void SimonSays::rules(){
	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "                                RULES:                                 \n" << endl;
	ansi.textAttr("-bold");
	
	cout << "Simon Says is a game where you will be shown a series of button presses\n" 
			"which you must then repeat back. The buttons used will be the four     \n"
			"arrow keys, presented to you in a random order. You must repeat back   \n"
			"the same arrow keys in the exact same order they were presented to you.\n"
			"When you fail to press the currect buttons in the correct order, the   \n"
			"game will be over, and your final score will be the number of turns you\n"
			"survived.                                                              \n"<< endl;

	ansi.textAttr("bold");
	cout << "                              CONTROLS:                                \n" << endl;
	ansi.textAttr("-bold");

	cout << "                   [Arrow keys] - Copy Simon's moves                   \n" << endl;

	ansi.textAttr("bold");
	cout << "                  Press any key to return to the menu                  \n" << endl;
	ansi.textAttr("-bold");
	getch();
	ansi.textReset();
}