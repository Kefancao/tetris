#ifndef __LEVEL3_H__
#define __LEVEL3_H__
#include "level.h" 
#include "blocksList.h"
#include <string> 
#include <fstream> 

using std::string; 

class Level3 : public Level{
	// For the norandom command. 
	bool random = true; 
	string fileName; 
	std::ifstream inFile; 

	public: 
		Level3(int seed); 
		shared_ptr<Block> make(BlockTypes force = BlockTypes::Nothing) override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
		int getLevel() override;

		// controlls if Blocks are randomly generated or use the inFile
		void setRandomOff(string _fileName); 
		void setRandomOn(); 
		bool getRandom(); 
}; 

#endif
