#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector> 
#include <memory> 
#include <utility>
#include <string>
#include "command.h"
#include "coordinates.h"
#include "blocksList.h"

using std::string; 
using std::vector; 
using std::shared_ptr; 
using std::pair;

class Level; 
class Block;
class Cell;
class TextDisplay;
class GraphicalDisplay;

class Board {

	// lists all of the current blocks (used for scoring)
	vector<shared_ptr<Block>> blocks;
	int score; 

	shared_ptr<Level> factory; 
	shared_ptr<Block> cur; 
	shared_ptr<Block> next; 

	vector<vector<shared_ptr<Cell>>> grid; 

	// for displaying the next block
	vector<vector<shared_ptr<Cell>>> nextGrid; 
	
	shared_ptr<TextDisplay> td; 
	shared_ptr<GraphicalDisplay> gui;

	int myNum;
	bool blind;

	string fileName; 

	public: 
		Board(Coordinates textCoord, bool textGUI, string inFileName = "sequence.txt", 
			shared_ptr<GraphicalDisplay> gui = nullptr, int myNum = 0, int initLvl = 0, int seed = 0);
	
		int getLevel(); 
		int getScore();

		shared_ptr<TextDisplay> getTD(); 

		// sets the blind status of certain Cells
		void setBlind(bool _blind); 

		bool isCurrentHeavy();
		void makeCurrentHeavy();

		void setRandom(bool random); 
 
		// prints the specified row of the grid
		void printLine(int row); 

		// prints the specified row of the nextGrid
		void printLineNext(int row);

		void increaseLevel(int mult); 
		void decreaseLevel(int mult); 

		// drops the current block and does neccessary updates,
		// returns the number of rows cleared or -1 for game over
		int dropBlock();

		// moves the current block according to the Command
		// the int is the multiplicity of the movement
		// returns true if the block was able to move
		bool moveBlock(pair<Command, int> cmd);

		// makes the current Block be the Block specified by cmd
		bool force(Command cmd);

	private:

		bool moveBlockOnce(Command cmd);

		// makes a new current block
		bool blockCreate();

		// makes and drops a brown block if appropriate
		bool brownBlockCreate();

		// sets a Cell to point at the block
		// Cell notifies its observers if notify is true
		void setCell(Coordinates c, shared_ptr<Block> block, bool notify); 

		// sets a Cell in the nextGrid to point at the block
		// Cell always notifies its observers
		void setCellNext(Coordinates c, shared_ptr<Block> block);

		// clears the next display
		void clearNext();

		// clears the full rows and returns the number of rows cleared
		int clearRows();

		// returns true if the move is succesful
		//	 checks if the current block is not overlapping with other blocks
		//	 and that it is still on the grid
		bool successfulMove();

}; 

#endif 
