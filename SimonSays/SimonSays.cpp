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
		cout << endl;
		cout << "                                       Welcome to Simon Says!                                      \n" 
				"                             Please select an option from the menu below:                          \n" << endl << endl;

		cout << "                             (1) Play Simon Says                                                   \n" << endl;
		
		cout << "                             (2) View high scores\n"
				"                             (3) View game rules and controls\n" << endl;

		cout << "                             (0) Return to GameHub							                         " << endl;
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
	bool gameOver = false;		// keep track of if the game is over
	int moveKey;				// For getch()
	moves = {};					// Initialize the list of moves as an empty list
	score = 0;					// Initialize the score at 0

	srand((unsigned)time(0));	// Set random seed for move generation

	// Main game loop
	while(!gameOver){
		// Print the current move
		printKeys(movenone, gameOver);
		Sleep(500);

		// Generates simon's next move
		int pickMove = rand()%(4);
		switch(pickMove){
			case 0: moves.push_back(moveup); break;
			case 1: moves.push_back(movedown); break;
			case 2: moves.push_back(moveleft); break;
			case 3: moves.push_back(moveright); break;
		}

		// Display the order of moves that the user must recreate
		for(Move& m : moves){
			printKeys(m, gameOver);
			Sleep(500);

			// So that there is a gap between displaying each move in the sequence
			printKeys(movenone, gameOver);
			Sleep(100);
		}	

		// Input loop for user to recreate sequence of moves
		for(Move& m : moves){
			// Get key input from getch()
			moveKey = getch();
			// If it is an arrow key, use getch() again to get key value
			if(moveKey == 224)
				moveKey = getch();
			// Quit out of the game if user presses 'q'
			else if(moveKey == 'q')
				return;
			
			// Display the user's move
			if((moveKey == KEY_UP && m == moveup)||
				(moveKey == KEY_DOWN && m == movedown)||
				(moveKey == KEY_LEFT && m == moveleft)||
				(moveKey == KEY_RIGHT && m == moveright)){
				printKeys(m, gameOver);
			}
			// If they didn't press the right key, game is over
			else{
				gameOver = true;
				printKeys(movenone, gameOver);
				endgame();		// End game screen
				break;
			}
		}
		// If the user entered the correct sequence, increment the score 
		// and light up all squares to show the user they were successfull
		if(!gameOver){
			score++;
			printKeys(moveall, gameOver);

			Sleep(1000);
		}
	}
}

// Prints the images of the keys to the cmd window
void SimonSays::printKeys(Move dir, bool gameOver){
	// Print the header
	printHeader(); 
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << endl;

	// Print the up arrow symbol
	for(int i=0; i<4; i++){
		cout << "                                            ";
		if(dir==moveup || dir==moveall)				// If the up arrow is the current move, highlight it
			ansi.textAttr("reverse");
		cout << "^^^^^^^^^\n";
		if(dir==moveup || dir==moveall)
			ansi.textAttr("-reverse");
	}

	// Print the left and right arrow symbols
	for(int i=0; i<4; i++){
		cout << "                                   ";
		if(dir==moveleft || dir==moveall)			// If the left arrow is the current move, highlight it
			ansi.textAttr("reverse");
		cout << "<<<<<<<<<";
		if(dir==moveleft || dir==moveall)
			ansi.textAttr("-reverse");

		cout << "         ";
		if(dir==moveright || dir==moveall)			// If the right arrow is the current move, highlight it
			ansi.textAttr("reverse");
		cout << ">>>>>>>>>" << endl;
		if(dir==moveright || dir==moveall)
			ansi.textAttr("-reverse");
	}

	// Print the down arrow symbol
	for(int i=0; i<4; i++){
		cout << "                                            ";
		if(dir==movedown || dir==moveall)			// If the down arrow is the current move, highlight it
			ansi.textAttr("reverse");
		cout << "vvvvvvvvv\n";
		if(dir==movedown || dir==moveall)
			ansi.textAttr("-reverse");
	}

	cout << endl << endl;

	// If the game is not over, print the current score and controls underneath the arrow symbols
	if(!gameOver){
		cout << endl;
		cout << "                                             Score: " << score << endl << endl << endl << endl;
		ansi.textAttr("-bold");
		cout << "                        [Arrow Keys] - Copy Simon's moves         [q] - Quit                        " << endl << endl;
	}
	
	// Reset ansi escape attributes
	ansi.textReset();
}

// End game 
void SimonSays::endgame(){
	string in, scoreName;
	int num;

	// Alert the user that they pressed the wrong button and that the game is now over, and display their final score
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "                                  Sorry, wrong button. Game over!                                  " << endl << endl;
	cout << "                                          Final score: " << score << endl;
	
	// Check the high scores to see if it is a new high score
	inFile.open(HSFile);		// Open high score file
	if(!inFile.is_open()){		// If it is not open, there are no saved scores, meaning that this is a high score
		cout << "                                          ";
		ansi.textAttr("reverse");
		cout << "New high score!";				// Alert the user they got a new high score
		ansi.textAttr("-reverse");
		cout << "                               " << endl << endl;
	}
	else{
		getline(inFile, in);					// Get the first line from the high score file
		istringstream iss(in);
		iss >> in >> num;						// Get the high score from the first line

		// Check if the score is a higher than the high score
		if(score>num){
			cout << "                                          ";
			ansi.textAttr("reverse");
			cout << "New high score!";			// Alert the user they got a new high score
			ansi.textAttr("-reverse");
			cout << "                               " << endl << endl;
		}
		else
			// If they did not get a high score, show the current high score
			cout << "                                      High score to beat: " << num << endl << endl;
	}
	inFile.close();			// CLose the high score file

	// Ask for the users name to save their score
	cout << "                              Enter your name to save your score: ";
	cin >> scoreName;

	// Save the user's score
	updateHighScores(scoreName);
}

// Updates the high score file with a new score
void SimonSays::updateHighScores(string name){
	vector<string> hsList;			// To store the high scores
	string in, numname;
	int num;
	bool recorded = false;			// To keep track of if the current score has been inputted
	inFile.open(HSFile);			// Open the high score file

	// IF the file is not open, there are not high scores, so save the current high score as the only score
	if(!inFile.is_open()){
		inFile.close();
		outFile.open(HSFile);
		outFile << name << " " << score;
		outFile.close();
	}
	else{
		// Read through the lines in the file
		while(getline(inFile, in)){
			istringstream iss(in);
			iss >> numname >> num;			// Get the name and score from the line

			// If the user's score is better than the current score in the list, insert it into the vector in front of the current score
			if(score>num && !recorded){
				hsList.push_back(name + " " + to_string(score));
				recorded = true;
			}
			// Insert the current score and name in the vector
			hsList.push_back(in);
		}

		// If the user's score hasn't been inserted yet, insert it at the back of the vector
		if(!recorded)
			hsList.push_back(name + " " + to_string(score));

		// Close the file
		inFile.close();

		// Open the high score file to read from
		outFile.open(HSFile, ios::out | ios::trunc);

		// If it's open, enter in the top ten scores into the vecotr into the file
		if(outFile.is_open()){
			if(hsList.size()<10){
				for(int i=0; i<hsList.size(); i++){
					outFile << hsList[i] << endl;
				}
			}
			// If there are less than 10 scores in the vector, enter all the scores
			else{
				for(int i=0; i<10; i++){
					outFile << hsList[i] << endl;
				}				
			}
		}
		// Close the file
		outFile.close();
	}
}

// Prints all the high scores
void SimonSays::printHighScores(){
	string numsname, in;
	int num, i=1;

	// Print the header
	printHeader();
    ansi.textColor("green");
    ansi.textAttr("bold");

    cout << "                                          High Scores                                            \n" << endl << endl;

    ansi.textAttr("-bold");

    // Open high scores file
    inFile.open(HSFile);

    // If the file is not open, there are no saved scores
    if(!inFile.is_open()){
    	// Tell the user that there are no saved scores
    	cout << "                            There are no high score records available.                             \n"
    			"                          Please play the game to save some high scores.                           \n" << endl;

    	// Exit to Simon Says menu
    	cout << "\n\n\n";
		cout << "                               Press any key to return to the menu                                   " << endl;
		getch();
    }
    else{
    	// Read through the file line by line
    	while(getline(inFile, in)){
			istringstream iss(in);
			iss >> numsname >> num; 		// Get the name and score for the current line
			ansi.textAttr("bold");
			// Output the score. If statements are simply for display formatting purposes
			if(i<10)
				cout << "                                    " << i << ". " ;
			else
				cout << "                                   " << i << ". ";

			if(num<10)
				cout << " " << num;
			else
				cout << num;

			ansi.textAttr("-bold");
			// Output the name for the score
			cout << " ........... by " << numsname << endl;

			i++;
    	}

    	// Close the file
    	inFile.close();

    	
    	cout << "\n\n\n";
    	cout << "                                Press any key to return to the menu                                  " << endl;
    	getch();
    }
}

// Prints the header
void SimonSays::printHeader(){
    ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+-------------------------------------------------------------------------------------------------+\n"
			"|                                                                                                 |\n" 
			"|                 XXXXX  XXXXX  XXXXX  XXXXX  X   X    XXXXX  XXXXX  X   X  XXXXX                 |\n" 
			"|                 X        X    X X X  X   X  XX  X    X      X   X  X   X  X                     |\n" 
			"|                 XXXXX    X    X X X  X   X  X X X    XXXXX  XXXXX  XXXXX  XXXXX                 |\n"
			"|                     X    X    X X X  X   X  X  XX        X  X   X    X        X                 |\n"
			"|                 XXXXX  XXXXX  X X X  XXXXX  X   X    XXXXX  X   X    X    XXXXX                 |\n"
			"|                                                                                                 |\n"
			"+-------------------------------------------------------------------------------------------------+\n" << endl;
	ansi.textReset();
}

// Prints the game rules
void SimonSays::rules(){
	printHeader();
	ansi.textColor("green");
	ansi.textAttr("bold");
	cout << "                                              RULES:                                               \n" << endl;
	ansi.textAttr("-bold");
	
	cout << "              Simon Says is a game where you will be shown a series of button presses              \n" 
			"              which you must then repeat back. The buttons used will be the four                   \n"
			"              arrow keys, presented to you in a random order.                                      \n"
			"              You must repeat back the same arrow keys in the exact same order they                \n"
			"              were presented to you.\n"
			"              Every turn, if you correctly enter the keys in the correct order, the                \n"
			"              displayed keys will all flash to signify that you repeated the sequence              \n"
			"              correctly.\n"
			"              When you fail to press the keys in the correct order, the game will be               \n"
			"              over, and your final score will be the number of turns you survived.                 \n"<< endl;

	ansi.textAttr("bold");
	cout << "                                            CONTROLS:                                              \n" << endl;
	ansi.textAttr("-bold");

	cout << "                                 [Arrow keys] - Copy Simon's moves                                 \n" << endl;

	ansi.textAttr("bold");
    cout << "\n\n\n";
	cout << "                                Press any key to return to the menu                                \n" << endl;
	ansi.textAttr("-bold");
	getch();
	ansi.textReset();
}