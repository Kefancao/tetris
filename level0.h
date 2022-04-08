#ifndef __LEVEL0_H__
#define __LEVEL0_H__
#include "level.h" 
#include <string> 
#include <fstream> 
#include <memory>

using std::string; 

class Level0 : public Level{
		std::ifstream inFile; 
		string fileName; 
	public: 
		Level0(int seed); 
		shared_ptr<Block> make(BlockTypes force = BlockTypes::Nothing) override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
		int getLevel() override;
		void setFileName(string _fileName); 
}; 

#endif
