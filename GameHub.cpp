#include "TicTacToe/TicTacToe.h"
#include "SimonSays/SimonSays.h"
#include "Memory/Memory.h"
#include "ConnectFour/ConnectFour.h"

using namespace std;

dispANSI ansi;

void printTitle();
void mainScreen();
int mainMenu();

int main(){
	system("CLS");
	ansi.windowSize(100, 33);
	ansi.showCursor(false);

	mainScreen();

	int menuChoice;
	do{
		menuChoice = mainMenu();

		if(menuChoice==1){
			TicTacToe ticTac;
			ticTac.start();
		}
		else if(menuChoice==2){
			SimonSays simonSays;
			simonSays.start();
		}
		else if(menuChoice==3){
			Memory memory;
			memory.start();
		}
		else if(menuChoice==4){
			ConnectFour connectfour;
			connectfour.start();
		}
	}while(menuChoice!=0);

	ansi.textReset();
	ansi.clearScreen();
	ansi.showCursor(true);

	return 0;
}

void mainScreen(){
	string name;
	printTitle();
    ansi.textColor("green");
	cout << " |                 Version 1.0                 |           Created By: Alex Salmi                |" << endl;
	cout << " \\_____________________________________________|_________________________________________________/" << endl;
	cout << "\n\n\n\n\n\n";
	ansi.textAttr("bold");
	cout << "                                    Press any button to begin                                     " << endl;
	ansi.textReset();

	getch();
}

int mainMenu(){
	int menuChoice;
	while(true){
		// Print header and change text attributes
		printTitle();
		ansi.textColor("green");
		ansi.textAttr("bold");
		cout << "\n\n";

		// Print the menu options to the cmd window
		cout << "                                        Welcome to GameHub!                                        \n" 
				"                                 What game would you like to play?                               \n\n" << endl;

		cout << "                                 (1) Tic Tac Toe                                                   \n"
				"                                 (2) Simon Says                                                    \n" 
				"                                 (3) Memory                                                        \n"
				"                                 (4) Connect Four ";
		ansi.textAttr("-bold");
		cout << "(In Progress)\n";
		ansi.textAttr("bold"); 
		cout << "                                 ( ) Mastermind   ";
		ansi.textAttr("-bold");
		cout << "(Coming Soon!)\n";
		ansi.textAttr("bold"); 	 
		cout << "                                 ( ) Hangman      ";
		ansi.textAttr("-bold");
		cout << "(Coming Soon!)\n\n\n";
		ansi.textAttr("bold"); 

		cout << "                                 (0) Quit GameHub			                                         " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice <= 4 && menuChoice >= 0)
			return menuChoice;		
	}
}

void printTitle(){
    ansi.clearScreen();
    ansi.textAttr("bold");
    ansi.textColor("green");
		cout << "  _______________________________________________________________________________________________  \n"
				"//                                                                                               \\\\\n"
				"++-----------------------------------------------------------------------------------------------++\n"
				"||                  XXXXXXXX                           XXX  XXX                                  ||\n"
				"||                  XXXXXXXX  XXXXXX  XXX XXX  XXXXXX  XXX  XXX  X    X  XXXXX                   ||\n"
				"||                  XXX       X    X  X  X  X  X       XXX  XXX  X    X  X    X                  ||\n"
				"||                  XXX XXXX  XXXXXX  X  X  X  XXXX    XXXXXXXX  X    X  XXXXX                   ||\n"
				"||                  XXX   XX  X    X  X  X  X  X       XXXXXXXX  X    X  X    X                  ||\n"
				"||                  XXXXXXXX  X    X  X  X  X  XXXXXX  XXX  XXX  XXXXXX  XXXXX                   ||\n"
				"||                  XXXXXXXX                           XXX  XXX                                  ||\n"
				"++-----------------------------------------------------------------------------------------------++\n"
				"\\\\_______________________________________________________________________________________________//\n";
	ansi.textReset();
}