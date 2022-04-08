#ifndef __LEVEL4_H__
#define __LEVEL4_H__
#include "level.h" 
#include "blocksList.h"
#include <string> 
#include <fstream> 

using std::string; 

class Level4 : public Level{
		// Keeps track how many turns it has been since cleared
		int turns; 
		// Cleared to indicate the state of the program. 
		bool cleared; 
		bool random = true; 
		// For the norandom command. 
		string fileName; 
		std::ifstream inFile;
	public:
		Level4(int seed); 
		shared_ptr<Block> make(BlockTypes force = BlockTypes::Nothing) override; 
		shared_ptr<Level> increase() override; 
		shared_ptr<Level> decrease() override; 
		int getLevel() override;

		// returns a pointer to a brown Block
		shared_ptr<Block> makeBrown(); 
		// returns true if it is the appropriate conditions
		//   for making a brown Block
		bool isMakeBrown(); 
		void setCleared(bool _cleared); 

		// controlls if Blocks are randomly generated or use the inFile
		void setRandomOff(string _fileName); 
		void setRandomOn(); 
		bool getRandom(); 
}; 

#endif
