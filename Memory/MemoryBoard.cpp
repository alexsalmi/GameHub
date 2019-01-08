#include "MemoryBoard.h"

MemoryBoard::MemoryBoard(){
	rows = 5;
	cols = 5;
	cursX = cols/2;
	cursY = rows/2;

	init();
}

MemoryBoard::MemoryBoard(int r, int c){
	rows = r;
	cols = c;
	cursX = cols/2;
	cursY = rows/2;

	init();
}

void MemoryBoard::init(){
	std::vector<char> vecChar;
	std::vector<bool> vecBool;
	int i, symbol, r, c;
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
	board[rows/2][cols/2] = '-';
	showBoard[rows/2][cols/2] = true;

	for(i=0; i<NUMSYMBOLS; i++)
		symbolsUsed[SYMBOLS[i]] = false;

	srand((unsigned)time(0));
	int syms[(rows*cols)/2];
	for(i=0; i<(rows*cols)/2; i++){
		do{
			symbol = rand()%(NUMSYMBOLS);
		}while(symbolsUsed[SYMBOLS[symbol]]);
		symbolsUsed[SYMBOLS[symbol]] = true;
		syms[i] = SYMBOLS[symbol];
		pairsLeft++;
	}

	for(i=0; i<(rows*cols)/2; i++){
		do{
			r = rand()%(rows);
			c = rand()%(cols);
		}while(board[r][c]!=' ');
		board[r][c] = syms[i];
		do{
			r = rand()%(rows);
			c = rand()%(cols);
		}while(board[r][c]!=' ');
		board[r][c] = syms[i];
	}
}

void MemoryBoard::update(int moveKey){
	if(choice==waiting){
		choice = first;
		showBoard = tempBoard;
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
		case ' ':
			if(!showBoard[cursY][cursX]){
				if(choice==first){
					tempBoard = showBoard;
					showBoard[cursY][cursX] = true; 
					choice = second;
					firstChoice = board[cursY][cursX];
				}
				else if(choice==second){
					showBoard[cursY][cursX] = true; 
					if(firstChoice == board[cursY][cursX]){
						pairsLeft--;
						choice = first;
					}
					else
						choice = waiting;
				}
			}
			break;
		default:break;
	}
	return;
}

void MemoryBoard::print(){
	int i,j;
	ansi.textAttr("bold");
	ansi.textColor("green");

	cout << "                                        ";
	for(i=0; i<cols*4-1; i++)
		cout << "_";
	cout << "\n";
	for(i=0; i<rows; i++){
		cout << "                                       |";
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
		cout << "                                       |";
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