#ifndef __GAME_H__
#define __GAME_H__
#include <memory>
#include <utility>
#include <string>
#include <fstream> 
#include <iostream>
#include <map>
#include "command.h"

class Board;
class GraphicalDisplay;

class Game{

	std::shared_ptr<Board> player1; 
	std::string inFile1; 

	std::shared_ptr<Board> player2; 
	std::string inFile2; 

	std::shared_ptr<Board> cur; 

	bool singlePlayer;
	 
	int highScore; 

	std::shared_ptr<GraphicalDisplay> gui; 

	bool textGUI;

	int initLvl; // starts the Board at this level

	std::shared_ptr<std::ifstream> in; // sequence input file
	int sequenceCount;	// multiplicity of sequnce command

	int seed; 


	// dictionary of commands and their names
	std::map<std::string, Command> commandPairs = {
		{"left", Left}, {"right", Right}, 
		{"clockwise", Clockwise}, {"countclockwise", Counterclockwise},
		{"down", Down},{"drop", Drop}, 
		{"levelup", LevelUp}, {"leveldown", LevelDown},
		{"restart", Restart},
		{"I", I}, {"J", J}, {"L", L}, {"O", O}, {"S", S}, {"T", T}, {"Z", Z},
		{"hint", Hint}, 
		{"random", Random}, {"norandom", NoRandom},
		{"sequence", Sequence}
	};


	public: 

		Game(std::string inFile1="sequence1.txt", std::string inFile2="sequence2.txt", bool textOnly=false, 
			bool textGUI = false, int initLvl = 0, int seed = 0); 
		
		// starts a game
		void playGame();


	private:

		// reads in a string (either from cin or in) into s
		void readString(std::string& s);

		// resets the game
		void newGame(); 

		// switches the current Board 
		void switchBoard();

		void updateHighScore(); 

		// prints out the game (both Boards side by side)
		void print();

		// gives a game over message and can restart the game
		void gameOver();

		// asks player for special action and applies it to the other player 
		void specialAction();

		// prints out a list of the commands
		void showHint();

		// matches user input to a Command and a multiplicity
		std::pair<Command, int> determineCmd(); 

		// does the specified Command (usually by calling Board methods)
		void doCmd(std::pair<Command, int> cmd); 
}; 

#endif 
