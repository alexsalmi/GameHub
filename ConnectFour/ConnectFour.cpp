#include "ConnectFour.h"

ConnectFour::ConnectFour(){};

void ConnectFour::start(){
	int menuChoice;	
	do{
		menuChoice = menu();

		switch(menuChoice){
			case 1: play(); break;
			case 2: play(); break;
			case 3: rules(); break;
			default: break;
		}
	}while(menuChoice!=0);
}

int ConnectFour::menu(){ 
	int menuChoice;

	while(true){
		// Print header and change text attributes
		printHeader(); 
		ansi.textColor("green");
		ansi.textAttr("bold");

		// Print the menu options to the cmd window
		cout << endl;
		cout << "                                       Welcome to Connect Four!                                    \n" 
				"                             Please select an option from the menu below:                          \n" << endl << endl;

		cout << "                             (1) Play Connect Four vs. the CPU    (1 Player)                       \n"
				"                             (2) Play Connect Four vs. a friend   (2 Player)                       \n" << endl;
		
		cout <<	"                             (3) View game rules and controls\n" << endl;

		cout << "                             (0) Return to GameHub							                         " << endl;
		ansi.textReset();

		// Accept the user's input
		cin >> menuChoice;
		// Error check for invalid input
		if(cin.fail()){
			cin.clear();
        	cin.ignore();
		}
		else if(menuChoice<=3 && menuChoice>=0){
			return menuChoice;
		}
	}
}

void ConnectFour::play(){
	CFBoard gameBoard;

	printHeader();
	cout << "\n\n\n";
	gameBoard.print();
}

void ConnectFour::printHeader(){
	ansi.clearScreen();
    ansi.textColor("green");
    ansi.textAttr("bold");
	cout << "+-------------------------------------------------------------------------------------------------+\n"
			"|                                                                                                 |\n" 
			"|          XXXXX  XXXXX  X   X  X   X  XXXXX  XXXXX  XXXXX    XXXXX  XXXXX  X   X  XXXXX          |\n" 
			"|          X      X   X  XX  X  XX  X  X      X        X      X      X   X  X   X  X   X          |\n" 
			"|          X      X   X  X X X  X X X  XXX    X        X      XXXX   X   X  X   X  XXXXX          |\n"
			"|          X      X   X  X  XX  X  XX  X      X        X      X      X   X  X   X  XXXX           |\n"
			"|          XXXXX  XXXXX  X   X  X   X  XXXXX  XXXXX    X      X      XXXXX  XXXXX  X   X          |\n"
			"|                                                                                                 |\n"
			"+-------------------------------------------------------------------------------------------------+\n" << endl;
	ansi.textReset();
}

void ConnectFour::rules(){

}