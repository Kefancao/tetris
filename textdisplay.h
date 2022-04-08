#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <vector> 
#include <iostream>
#include <string>
#include "observer.h"
#include "coordinates.h"

using std::ostream; 
using std::string; 

class TextDisplay: public Observer{
	std::vector<std::vector<char>> board; 
	std::vector<std::vector<char>> next;
	Coordinates myCoord; 
	bool textGUI; 
	int highScore; 
	int score; 
	int level; 
	const int end = 27; 
	public: 
		TextDisplay(Coordinates myCoord, bool textGUI); 
		// Notifies the board. 
		void notify(Cell &whoNotified) override;
		// Prints the textGUI feature
		void print(); 
		// Prints a single line 
		void printLine(int row); 
		void printLineNext(int row);
		// Updating score and level
		void setScore(int _score, int highScore = -1); 
		void setLevel(int _level); 
		// For prompting the user in GUI mode
		char playAgain(string prompt); 
		string specialAction(); 
		// Displays the textGUI
		void display();
}; 

#endif 
