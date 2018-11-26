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
			case 1: play(); break;				// Play Simon Says
			case 2: printHighScores(); break;	// Show the high scored for Simon Says
			case 3: rules(); break;				// Rules of Simon Says
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
		else if(menuChoice<=3 && menuChoice>=0)
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
			else if(moveKey == 'q')
				return;
			
			if((moveKey == KEY_UP && m == moveup)||
				(moveKey == KEY_DOWN && m == movedown)||
				(moveKey == KEY_LEFT && m == moveleft)||
				(moveKey == KEY_RIGHT && m == moveright)){
				printKeys(m, gameOver);
			}
			else{
				gameOver = true;
				printKeys(movenone, gameOver);
				endgame();
				break;
			}
		}
		if(!gameOver){
			score++;
			printKeys(moveall, gameOver);

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
		if(dir==moveup || dir==moveall)
			ansi.textAttr("reverse");
		cout << "^^^^^^^\n";
		if(dir==moveup || dir==moveall)
			ansi.textAttr("-reverse");
	}


	for(int i=0; i<3; i++){
		cout << "                        ";
		if(dir==moveleft || dir==moveall)
			ansi.textAttr("reverse");
		cout << "<<<<<<<";
		if(dir==moveleft || dir==moveall)
			ansi.textAttr("-reverse");

		cout << "       ";
		if(dir==moveright || dir==moveall)
			ansi.textAttr("reverse");
		cout << ">>>>>>>" << endl;
		if(dir==moveright || dir==moveall)
			ansi.textAttr("-reverse");
	}

	for(int i=0; i<3; i++){
		cout << "                               ";
		if(dir==movedown || dir==moveall)
			ansi.textAttr("reverse");
		cout << "vvvvvvv\n";
		if(dir==movedown || dir==moveall)
			ansi.textAttr("-reverse");
	}

	cout << endl << endl;

	if(!gameOver){
		cout << "                               Score: " << score << endl << endl;
		ansi.textAttr("-bold");
		cout << "          [Arrow Keys] - Copy Simon's moves         [q] - Quit          " << endl << endl;
	}
	
	ansi.textReset();
}

void SimonSays::endgame(){
	string in, scoreName;
	int num;

	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "                    Sorry, wrong button. Game over!                      " << endl << endl;
	cout << "                            Final score: " << score << endl;
	
	inFile.open(HSFile);
	if(!inFile.is_open()){
		cout << "                            ";
		ansi.textAttr("reverse");
		cout << "New high score!";
		ansi.textAttr("-reverse");
		cout << "                               " << endl << endl;
	}
	else{
		getline(inFile, in);
		istringstream iss(in);
		iss >> in >> num;

		if(score>num){
			cout << "                            ";
			ansi.textAttr("reverse");
			cout << "New high score!";
			ansi.textAttr("-reverse");
			cout << "                               " << endl << endl;
		}
		else
			cout << "                        High score to beat: " << num << endl << endl;
	}
	inFile.close();

	cout << "                Enter your name to save your score: ";
	cin >> scoreName;

	updateHighScores(scoreName);
}

// Updates the high score file with a new score
void SimonSays::updateHighScores(string name){
	vector<string> hsList;
	string in, numname;
	int num;
	bool recorded = false;
	inFile.open(HSFile);

	if(!inFile.is_open()){
		inFile.close();
		outFile.open(HSFile);
		outFile << name << " " << score;
		outFile.close();
	}
	else{
		while(getline(inFile, in)){
			istringstream iss(in);
			iss >> numname >> num;

			if(score>num && !recorded){
				hsList.push_back(name + " " + to_string(score));
				recorded = true;
			}
			hsList.push_back(in);
		}

		if(!recorded)
			hsList.push_back(name + " " + to_string(score));

		inFile.close();

		outFile.open(HSFile, ios::out | ios::trunc);

		if(outFile.is_open()){
			if(hsList.size()<10){
				for(int i=0; i<hsList.size(); i++){
					outFile << hsList[i] << endl;
				}
			}
			else{
				for(int i=0; i<10; i++){
					outFile << hsList[i] << endl;
				}				
			}
		}
		outFile.close();
	}
}

// Prints all the high scores
void SimonSays::printHighScores(){
	string numsname, in;
	vector<string> hsList;
	int num, i=1;

	printHeader();
    ansi.textColor("green");
    ansi.textAttr("bold");

    cout << "                            High Scores                              \n" << endl << endl;

    ansi.textAttr("-bold");

    inFile.open(HSFile);

    if(!inFile.is_open()){
    	cout << "              There are no high score records available.               \n"
    			"            Please play the game to save some high scores.             \n" << endl;

    	// Exit to Simon Says menu
		cout << "                  Press any key to return to the menu                    " << endl;
		getch();
    }
    else{
    	while(getline(inFile, in)){
			istringstream iss(in);
			iss >> numsname >> num;
			ansi.textAttr("bold");
			if(i<10)
				cout << "                      " << i << ". " ;
			else
				cout << "                     " << i << ". ";

			if(num<10)
				cout << " " << num;
			else
				cout << num;

			ansi.textAttr("-bold");
			cout << " ........... by " << numsname << endl;

			i++;
    	}

    	inFile.close();

    	cout << endl << endl;

    	cout << "                  Press any key to return to the menu                    " << endl;
    	getch();
    }
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
			"arrow keys, presented to you in a random order.                        \n"
			"You must repeat back the same arrow keys in the exact same order they  \n"
			"were presented to you.\n"
			"Every turn, if you correctly enter the keys in the correct order, the  \n"
			"displayed keys will all flash to signify that you repeated the sequence\n"
			"correctly.\n"
			"When you fail to press the keys in the correct order, the game will be \n"
			"over, and your final score will be the number of turns you survived.   \n"<< endl;

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