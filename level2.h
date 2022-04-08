#ifndef __LEVEL2_H__
#define __LEVEL2_H__
#include "level.h" 
#include "blocksList.h"

class Level2 : public Level{
	public: 
		Level2(int seed); 
		shared_ptr<Block> make(BlockTypes force = BlockTypes::Nothing) override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
		int getLevel() override;
}; 

#endif
