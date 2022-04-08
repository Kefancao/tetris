#include <iostream> 
#include <vector> 
#include <string> 
#include <memory> 
#include "ncurses.h"
#include "textdisplay.h"
#include "coordinates.h"
#include "block.h"
#include "cell.h"

using std::cout; 
using std::endl; 
using std::shared_ptr; 
using std::string; 
using std::vector; 

const int BACKGROUND = 1; 
const int O_BLOCK = 2;
const int I_BLOCK = 3; 
const int J_BLOCK = 4; 
const int L_BLOCK = 5; 
const int S_BLOCK = 6; 
const int Z_BLOCK = 7; 
const int T_BLOCK = 8; 
const int TEXT = 9; 
const int BLIND = 10;
const int B_BLOCK = 11; 

TextDisplay::TextDisplay(Coordinates myCoord, bool textGUI) : myCoord{myCoord}, textGUI{textGUI}, highScore{-1}{
	board = vector<vector<char>>(18, vector<char>(11, ' '));
	next = vector<vector<char>>(2, vector<char>(4, ' '));  
}

static int mapVals(char c){
	int style; 
	switch (c){
		case ' ': style = BACKGROUND; break; 
		case 'O': style = O_BLOCK; break; 
		case 'L': style = L_BLOCK; break; 
		case 'J': style = J_BLOCK; break;
		case 'Z': style = Z_BLOCK; break;
		case 'S': style = S_BLOCK; break;
		case 'I': style = I_BLOCK; break;
		case 'T': style = T_BLOCK; break;
		case '*': style = B_BLOCK; break; 
		default: style = BLIND; break;
	}
	return style; 
}
void TextDisplay::print(){
	string line; 
	string borderLine(board[0].size(), '-');  
	int linesPrinted = highScore >= 0 ? 0 : 1; 
	borderLine = "x" + borderLine + "x"; 
	line = borderLine;  
	attron(COLOR_PAIR(TEXT)); 
	if (highScore >= 0){
		mvprintw(myCoord.y + linesPrinted, myCoord.x + 8, "High Score: %d", highScore); 
		++linesPrinted; 
	}
	mvprintw(myCoord.y + linesPrinted, myCoord.x, "Level:%7d", level); 
	++linesPrinted; 
	mvprintw(myCoord.y + linesPrinted, myCoord.x, "Score:%7d", score); 
	++linesPrinted; 
	mvprintw(myCoord.y + linesPrinted, myCoord.x, "%s", line.c_str()); 
	attroff(COLOR_PAIR(TEXT)); 
	++linesPrinted; 


	for (size_t i = 0; i < board.size(); ++i){
		line.clear(); 
		attron(COLOR_PAIR(TEXT)); 
		mvprintw(myCoord.y + i + linesPrinted, myCoord.x, "|"); 
		attroff(COLOR_PAIR(TEXT)); 
		for (size_t j = 0; j < board[i].size(); ++j){
			int style = mapVals(board[i][j]); 
			attron(COLOR_PAIR(style)); 
			printw("%c", board[i][j]); 
			attroff(COLOR_PAIR(style)); 
		}
		attron(COLOR_PAIR(TEXT)); 
		printw("|"); 
		attroff(COLOR_PAIR(TEXT));  
	}
	line.clear(); 
	line = borderLine; 
	mvprintw(myCoord.y + board.size() + linesPrinted, myCoord.x, "%s", line.c_str()); 
	++linesPrinted; 
	mvprintw(myCoord.y + board.size() + linesPrinted, myCoord.x, "Next: "); 
	++linesPrinted; 
	for (size_t i = 0; i < next.size(); ++i){
		move(myCoord.y + board.size() + i + linesPrinted, myCoord.x + 4);
		for (size_t j = 0; j < next[i].size(); ++j){
			int style = mapVals(next[i][j]); 
			attron(COLOR_PAIR(style)); 
			printw("%c", next[i][j]); 
			attroff(COLOR_PAIR(style)); 
		}
	}
	
	move(end, 0); 

}

void TextDisplay::printLine(int row){
	cout << "|";
	for(auto n : board[row]) cout << n; 
	cout << "|";
}

void TextDisplay::printLineNext(int row) {
	for(auto n : next[row]) cout << n; 
}

void TextDisplay::notify(Cell &whoNotified){
	int x = whoNotified.getX(); 
	int y = whoNotified.getY(); 
	char block = whoNotified.getBlockType(); 
	if (whoNotified.isNext()) next[y][x] = block;
	else board[y][x] = block;  
}

void TextDisplay::setScore(int _score, int _highScore){
	if (_highScore >= 0) highScore = _highScore; 
	score = _score; 
}
void TextDisplay::setLevel(int _level){
	level = _level; 
}

char TextDisplay::playAgain(string prompt){
	move(end, 0); 
	printw("%s", prompt.c_str());
	refresh(); 
	int c = getch(); 
	clrtoeol(); 
	move(end + 1, 0); 
	clrtoeol(); 
	move(end, 0); 
	clrtoeol(); 
	return c; 
}

string TextDisplay::specialAction(){
	move(end, 0); 
	printw("Enter special action\n - Blind (b)\n - Heavy (h)\n - Force (f)"); 
	int action = getch(); 
	for (int i = 0; i < 4; ++i){
		move(end + i, 0); 
		clrtoeol(); 
	}
	switch (action){
		case 'b': return "blind"; 
		case 'h': return "heavy"; 
		case 'f': return "force"; 
		default : return "blind"; 
	}
}

void TextDisplay::display(){
	if (textGUI){
		print(); 
		refresh(); 
	}
}