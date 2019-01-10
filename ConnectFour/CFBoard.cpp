#include "CFBoard.h"

CFBoard::CFBoard(){
	rows = 6;
	cols = 7;

	init();
}

CFBoard::CFBoard(int r, int c){
	rows = r;
	cols = c;

	init();
}

void CFBoard::init(){
	int r, c;

	cursor = cols/2;
	std::vector<int> vec;
	for(r=0; r<rows; r++){
		vec = {};
		for(c=0; c<cols; c++)
			vec.push_back(0);
		board.push_back(vec);
	}
}

void CFBoard::print(){
	ansi.textColor("green");
	ansi.textAttr("bold");
	int i, r, c;
	cout << "                                    ";
	for(i=0; i<cols; i++){
		if(cursor==i)
			cout << " v  ";
		else
			cout << "    ";
	}
	cout << "\n";

	cout << "                                   ";
	for(i=0; i<(cols*4)+1; i++)
		cout << "_";
	cout << "\n";

	for(r=0; r<rows; r++){
		cout << "                                   ";
		cout << "|";
		for(c=0; c<cols; c++){
			switch(board[r][c]){
				case 0: ansi.textColor("green"); break;
				case 1: ansi.textColor("blue"); break;
				case 2: ansi.textColor("red"); break;
			}
			cout << " O |";
		}
		ansi.textColor("green");
		cout << "\n                                   ";
		if(r!=(rows-1)){
			cout << "|";
			for(c=0; c<cols; c++)
				cout << "   |";
			cout << "\n";
		}
	}
	cout << "|";
	for(i=0; i<cols; i++)
		cout << "___|";
	cout << "\n";
	ansi.textReset();

	getch();
}