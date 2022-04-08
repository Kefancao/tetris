#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <memory>
#include <random> 
#include "block.h"
#include "blocksList.h"
#include "board.h"

using std::shared_ptr;

class Level{
	protected:
		// Random engine with its seed
		std::mt19937 gen;
		int seed; 
	public: 
		Level(int seed = 0); 

		// returns a Block pointer
		// - each concrete Level has different rules for making Blocks
		// - can force the Level to make the specified Block
		virtual shared_ptr<Block> make(BlockTypes force = BlockTypes::Nothing) = 0; 

		// returns a pointer to the next concrete Level
		virtual shared_ptr<Level> increase() = 0; 

		// returns a pointer to the previous concrete Level
		virtual shared_ptr<Level> decrease() = 0; 

		// returns what concrete Level I am
		virtual int getLevel() = 0;

		virtual BlockTypes charToBT(char c);
		virtual shared_ptr<Block> mapChar(BlockTypes type, bool heavy = false); 
}; 

#endif 
