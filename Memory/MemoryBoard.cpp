#include "MemoryBoard.h"

// Constructor
MemoryBoard::MemoryBoard(){
	// Sets the size of the board and centers the cursor on the board
	rows = 5;
	cols = 5;
	cursX = cols/2;
	cursY = rows/2;

	// Initializes the board values
	init();
}

// Constructor with custom board size
MemoryBoard::MemoryBoard(int r, int c){
	// Sets the size of the board and centers the cursor on the board
	rows = r;
	cols = c;
	cursX = cols/2;
	cursY = rows/2;

	// Initializes the board values
	init();
}

// Initializes the board values
void MemoryBoard::init(){
	std::vector<char> vecChar;	// Vector to fill board with chars
	std::vector<bool> vecBool;	// Vector to fill showBoard with false values
	int i, symbol, r, c;

	// Fills board with spaces and showBoard with falses
	for(int i=0; i<rows; i++){
		vecChar = {};
		vecBool = {};
		for(int j=0; j<cols; j++){
			vecChar.push_back(' ');
			vecBool.push_back(false);
		}
		board.push_back(vecChar);
		showBoard.push_back(vecBool);
	}
	// Displays the center tile 
	board[rows/2][cols/2] = '-';
	showBoard[rows/2][cols/2] = true;

	// Add all usable chars as keys to symbolsUsed, and set each value to false
	for(i=0; i<NUMSYMBOLS; i++)
		symbolsUsed[SYMBOLS[i]] = false;

	// Filling the board with pairs of chars
	srand((unsigned)time(0));		// Setting seed for rand()
	int syms[(rows*cols)/2];		// Keeping track of which symbols will be added to board
	for(i=0; i<(rows*cols)/2; i++){
		// Get a random available char from NUMSYMBOLS
		do{
			symbol = rand()%(NUMSYMBOLS);
		}while(symbolsUsed[SYMBOLS[symbol]]);

		// Set the char as true to indicate it's being used, and store the char in syms
		symbolsUsed[SYMBOLS[symbol]] = true;
		syms[i] = SYMBOLS[symbol];
		pairsLeft++;					// Keeps track of the number of pairs for the game logic
	}

	// Fill the board with the chosen random chars 
	for(i=0; i<(rows*cols)/2; i++){
		// Get random coordinates to place the char
		r = rand()%(rows);
		c = rand()%(cols);

		// While the coordinates are already occupied, move to the next tile until one is available
		while(board[r][c]!=' '){
			c++;
			if(c==cols){
				c=0;
				r=(r+1)%rows;
			}
		}
		// Place the char at the coordinates on the board
		board[r][c] = syms[i];

		// Repeat the same process for the second char in the pair
		r = rand()%(rows);
		c = rand()%(cols);
		while(board[r][c]!=' '){
			c++;
			if(c==cols){
				c=0;
				r=(r+1)%rows;
			}
		}
		board[r][c] = syms[i];
	}
}

// Updates the board after a move is made or the cursor is moved
void MemoryBoard::update(int moveKey){
	// If a move has been completed, move on to the next turn
	if(choice==waitingSuccess || choice==waitingFail){
		// If the completed move was not a match, hide the tiles again
		if(choice==waitingFail)
			showBoard = tempBoard;
		// Switch to state 'first'
		choice = first;
		return;
	}
	switch(moveKey){
		// Move curser up on board if possible
		case KEY_UP:
			if(cursY>0)
				cursY--;
			break;
		// Move curser down on board if possible
		case KEY_DOWN:
			if(cursY<rows-1)
				cursY++;
			break;
		// Move curser to the right on board if possible
		case KEY_RIGHT:
			if(cursX<cols-1)
				cursX++;
			break;
		// Move curser to the left on board if possible
		case KEY_LEFT:
			if(cursX>0)
				cursX--;
			break;
		// Choose the current tile
		case ' ':
			makeMove();
			break;
		default:break;
	}
	return;
}

// Decides wether a move is a match and resets the board if not
void MemoryBoard::makeMove(){
	// If the current tile is not hidden, exit function
	if(!showBoard[cursY][cursX]){
		// If we are in state 'first'
		if(choice==first){
			tempBoard = showBoard; 				// save the current board if the eventual move is not a match
			showBoard[cursY][cursX] = true; 	// SHow the current tile
			choice = second;					// Move on to state 'second'
			firstChoice = board[cursY][cursX];	// Save the char in the current tile, to be able to compare with the second choice
		}
		// If we are in state 'second'
		else if(choice==second){
			// Show the current tile
			showBoard[cursY][cursX] = true; 
			// If it is a match
			if(firstChoice == board[cursY][cursX]){
				choice = waitingSuccess;		// Move on to state 'waitingSuccess'
				pairsLeft--;					// Decrement number of remaining pairs
				// If game is over, move cursor to center
				if(pairsLeft==0){
					cursX = cols/2;
					cursY = rows/2;
				}
			}
			// If it is not a match, move on to state 'waitingFail'
			else
				choice = waitingFail;
		}
	}
}

// Prints the board to the cmd window
void MemoryBoard::print(){
	int i,j;
	ansi.textAttr("bold");
	ansi.textColor("green");

	if(rows==3)
		cout << "                                            ";
	else if(rows==5)
		cout << "                                        ";
	else if(rows==7)
		cout << "                                    ";

	for(i=0; i<cols*4-1; i++)
		cout << "_";
	cout << "\n";
	for(i=0; i<rows; i++){
		if(rows==3)
			cout << "                                           |";
		else if(rows==5)
			cout << "                                       |";
		else if(rows==7)
			cout << "                                   |";
		for(j=0; j<cols; j++){
			if(cursY==i && cursX==j)
				ansi.textAttr("reverse");
			if(showBoard[i][j])
				cout << " " << board[i][j] << " ";
			else
				cout << "   ";
			if(cursY==i && cursX==j)
				ansi.textAttr("-reverse");
			cout << "|";
		}
		cout << "\n";
		if(rows==3)
			cout << "                                           |";
		else if(rows==5)
			cout << "                                       |";
		else if(rows==7)
			cout << "                                   |";
		for(j=0; j<cols; j++){
			if(cursY==i && cursX==j)
				ansi.textAttr("reverse");
			cout << "___";
			if(cursY==i && cursX==j)
				ansi.textAttr("-reverse");
			cout << "|";
		}
		cout << "\n";
	}

	ansi.textReset();
}
