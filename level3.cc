#include "level4.h" 
#include "level3.h"
#include "level2.h" 
#include "level.h"
#include "blocksList.h"
#include "coordinates.h"
#include <random> 
#include <iostream> 

using std::shared_ptr; 
using std::make_shared; 
using std::discrete_distribution; 

Level3::Level3(int seed): Level{seed}, random{true}{} 

shared_ptr<Block> Level3::make(BlockTypes force){
	BlockTypes blockGen = force; 
	if (!random){
		char input = 'c'; 
		try{ 
			inFile >> input; 
		} catch (std::ios_base::failure&){
			inFile.clear(); 
			inFile.seekg(0, inFile.beg);
		}
		blockGen = charToBT(input); 
		if (blockGen == BlockTypes::Nothing) return make(); 
	}
	else{
		discrete_distribution<int> probs({0, 2, 2, 1, 1, 1, 1, 1}); 
		blockGen = force == BlockTypes::Nothing ? BlockTypes(probs(gen)) : force; 
	} 
	return mapChar(blockGen, true); 
}

// Make <Level1> into <Level1> 
shared_ptr<Level> Level3::increase(){
	shared_ptr<Level4> newLevel = make_shared<Level4>(seed); 
	return newLevel; 
}

// Make <Level0> into <Level1> 
shared_ptr<Level> Level3::decrease(){
	shared_ptr<Level2> newLevel = make_shared<Level2>(seed); 
	return newLevel; 
}

int Level3::getLevel() { return 3; }

void Level3::setRandomOff(string _fileName){
	bool restore = random; 
	random = false; 
	fileName = _fileName; 
	try{
		inFile = std::ifstream(fileName); 
		inFile.exceptions(std::ios_base::failbit); 
	} catch (std::ios_base::failure&){
		random = restore;
		std::cout << "Could not open input file" << std::endl;  
	}

}

void Level3::setRandomOn(){
	random = true;  
}

bool Level3::getRandom(){
	return random; 
}
