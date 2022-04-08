#ifndef __LEVEL1_H__
#define __LEVEL1_H__
#include "level.h" 

class Level1 : public Level{
	public: 
		Level1(int seed); 
		shared_ptr<Block> make(BlockTypes force) override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
		int getLevel() override;
}; 

#endif
