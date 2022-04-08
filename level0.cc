#include "level1.h" 
#include "level0.h" 
#include "blocksList.h"
#include "coordinates.h"
#include "breakException.h"
#include <random> 
#include <iostream> 

using std::discrete_distribution; 
using std::shared_ptr; 
using std::make_shared; 

Level0::Level0(int seed): Level{seed}, fileName{"sequence1.txt"} {
	inFile = std::ifstream(fileName); 
}

shared_ptr<Block> Level0::make(BlockTypes force){
	BlockTypes type = force;
	if (force == BlockTypes::Nothing) {
		char input = 'c'; 
		try{
			inFile >> input; 
		} catch (std::ios_base::failure&){
			inFile.clear(); 
			inFile.seekg(0, inFile.beg);
		} 
		type = charToBT(input);
		if (type == BlockTypes::Nothing) return make();
	} 
	return mapChar(type); 
}

// Make <Level0> into <Level1> 
shared_ptr<Level> Level0::increase(){
	shared_ptr<Level> newLevel = make_shared<Level1>(seed); 
	return newLevel; 
}

// Make <Level0> into <Level1> 
shared_ptr<Level> Level0::decrease(){
	shared_ptr<Level0> newLevel = make_shared<Level0>(seed); 
	return newLevel; 
}

int Level0::getLevel() { return 0; }

void Level0::setFileName(string _fileName){
	string restore = fileName; 
	fileName = _fileName; 
	try{
		inFile = std::ifstream(fileName); 
		inFile.exceptions(std::ios_base::failbit); 
	} catch (std::ios_base::failure&){
		fileName = restore; 
		std::cout << "Could not open input file for Level 0." << std::endl; 
		throw BreakException{}; 
	}
}
