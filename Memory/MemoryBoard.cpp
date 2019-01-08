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
	std::vector<char> vec;
	int i, symbol, r, c;
	for(int i=0; i<rows; i++){
		vec = {};
		for(int j=0; j<cols; j++){
			vec.push_back(' ');
		}
		board.push_back(vec);
	}
	board[rows/2][cols/2] = '-';

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
			cout << " " << board[i][j] << " ";
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
