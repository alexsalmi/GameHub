#include "MemoryBoard.h"

MemoryBoard::MemoryBoard(){
	rows = 7;
	cols = 9;
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
	for(int i=0; i<rows; i++){
		vec = {};
		for(int j=0; j<cols; j++){
			vec.push_back('x');
		}
		board.push_back(vec);
	}
}

void MemoryBoard::print(){
	ansi.textAttr("bold");
	ansi.textColor("green");

	for(int i=0; i<rows; i++){
		for(int j=0; j<(cols*2); j++)
			cout << "_";
		cout << "\n";
		for(int k=0; k<cols; k++)
			cout << board[i][k] << "|";
		cout << "\n";
	}

	for(int l=0; l<(cols*2); l++)
		cout << "_";
	cout << "\n";

	ansi.textReset();
}
