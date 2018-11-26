#ifndef DISPANSI
#define DISPANSI

using namespace std;

#include <string>
#include <vector>
#include <iostream>

class dispANSI{
public:
	// Constructor
	dispANSI();

	void clearScreen();
	void clearLine();

	void print(string text, std::vector<int> values);

	void textAttr(string attribute);

	void textColor(string color);

	void backgroundColor(string color);

	void textReset();

	void moveCursor(int row, int col);
	void moveCursor(string direction, int val=1);

	void saveCursor();
	void loadCursor();

	void windowSize(int w, int h);

	void showCursor(bool show);

private:	
	const char ESC = '\x1b';
};

#endif
