#ifndef __LEVELS_H__
#define __LEVELS_H__
#include "level.h"
#include "block.h"
#include <memory>

using std::shared_ptr; 

class Level0: public Level{
	public: 
		shared_ptr<Block> make() override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
};

class Level1: public Level{
	public: 
		shared_ptr<Block> make() override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
};

class Level2: public Level{
	public: 
		shared_ptr<Block> make() override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
};

class Level3: public Level{
	public: 
		shared_ptr<Block> make() override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
};

class Level4: public Level{
	int period; 
	public: 
		shared_ptr<Block> make() override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
}; 
 


#endif
