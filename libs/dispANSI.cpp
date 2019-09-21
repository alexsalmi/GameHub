#include "dispANSI.h"

dispANSI::dispANSI(){}

void dispANSI::clearScreen(){
	cout << ESC << "[2J";
}

void dispANSI::clearLine(){
	cout << ESC << "[K";
}

void dispANSI::print(string text, std::vector<int> values){
	if(values.size() > 0){
		int i=0;
		cout << ESC << '[';
		while(i<(values.size()-1)){
			cout << to_string(values[i++]) << ';';
		}
		cout << values[i] << 'm';
	}

	cout << text;

	textReset();
}

void dispANSI::textAttr(string attribute){
	cout << ESC << '[';
	if(attribute=="bold") cout << "1m";
	else if(attribute=="faint") cout << "2m";
	else if(attribute=="standout") cout << "3m";
	else if(attribute=="underline") cout << "4m";
	else if(attribute=="blink") cout << "5m";
	else if(attribute=="reverse") cout << "7m";
	else if(attribute=="-bold") cout << "22m";
	else if(attribute=="-faint") cout << "22m";
	else if(attribute=="-standout") cout << "23m";
	else if(attribute=="-underline") cout << "24m";
	else if(attribute=="-blink") cout << "25m";
	else if(attribute=="-reverse") cout << "27m";
}

void dispANSI::textColor(string color){
	cout << ESC << '[';
	if(color=="black") cout << "30m";
	else if(color=="red") cout << "31m";
	else if(color=="green") cout << "32m";
	else if(color=="yellow") cout << "33m";
	else if(color=="blue") cout << "34m";
	else if(color=="magenta") cout << "35m";
	else if(color=="cyan") cout << "36m";
	else if(color=="white") cout << "37m";
	else if(color=="reset") cout << "39m";
}

void dispANSI::backgroundColor(string color){
	cout << ESC << '[';
	if(color=="black") cout << "40m";
	else if(color=="red") cout << "41m";
	else if(color=="green") cout << "42m";
	else if(color=="yellow") cout << "43m";
	else if(color=="blue") cout << "44m";
	else if(color=="magenta") cout << "45m";
	else if(color=="cyan") cout << "46m";
	else if(color=="white") cout << "47m";
	else if(color=="reset") cout << "49m";
}

void dispANSI::textReset(){
	cout << ESC << "[0m";
}

void dispANSI::moveCursor(int row, int col){
	cout << ESC << '[' << to_string(row) << ';' << to_string(col) << 'f';
}

void dispANSI::moveCursor(string direction, int val){
	cout << ESC << '[' << to_string(val);
	if(direction=="up") cout << 'A';
	else if(direction=="down") cout << 'B';
	else if(direction=="right") cout << 'C';
	else if(direction=="left") cout << 'D';
}

void dispANSI::saveCursor(){
	cout << ESC << "[s";
}
void dispANSI::loadCursor(){
	cout << ESC << "[u";
}

void dispANSI::windowSize(int w, int h){
	cout << "\x1b[8;" << h << ";" << w << "t";
}

void dispANSI::showCursor(bool show){
	if(show)
		cout << "\x1b[?25h";
	else
		cout << "\x1b[?25l";

}
