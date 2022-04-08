#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <vector> 
#include "coordinates.h"

class Block {
	protected:
		int width, height;
		std::vector<Coordinates> positions; // positions on the grid
	private:
		bool heavy;
		int level; // level that created the block
		Coordinates getBottomLeft();
	public:
		Block(int width, int height, bool heavy);

		// moves the block's postions
		void left(); 
		void right(); 
		void clockwise(); 
		void counterclockwise(); 
		void down(); 
		void up();

		// returns the character that corresponds to the block type
		virtual char getType() const = 0;

		// getters and setters
		std::vector<Coordinates> getPositions() const;
		bool isHeavy() const;
		void makeHeavy();
		int getLevel() const;
		void setLevel(int _level);
}; 

#endif 
