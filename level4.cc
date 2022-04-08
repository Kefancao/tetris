#include "level2.h" 
#include "level4.h" 
#include "level3.h" 
#include "blocksList.h"
#include "level.h"
#include "coordinates.h"
#include <random>  
#include <iostream> 

using std::shared_ptr; 
using std::make_shared; 
using std::discrete_distribution; 
using std::cout; 
using std::endl; 

Level4::Level4(int seed): Level{seed}, turns{0}, cleared{false}{}

shared_ptr<Block> Level4::make(BlockTypes force){
	if (force == BlockTypes::Nothing) ++turns;  

	BlockTypes blockGen = force; 
	shared_ptr<Block> newBlock; 
	if (!random){
		char input = 'c'; 
		try{
			inFile >> input; 
		}
		catch(std::ios::failure&){
			inFile.clear(); 
			inFile.seekg(0, inFile.beg);
		}
		blockGen = charToBT(input); 
		if (blockGen == BlockTypes::Nothing) { --turns; return make();} 
	}
	else{
		discrete_distribution<int> probs({0, 2, 2, 1, 1, 1, 1, 1}); 
		blockGen = force == BlockTypes::Nothing ? BlockTypes(probs(gen)) : force; 
	}
	return mapChar(blockGen, true); 
}

// Make <Level1> into <Level1> 
shared_ptr<Level> Level4::increase(){
	shared_ptr<Level4> newLevel = make_shared<Level4>(seed); 
	return newLevel; 
}

// Make <Level0> into <Level1> 
shared_ptr<Level> Level4::decrease(){
	shared_ptr<Level3> newLevel = make_shared<Level3>(seed); 
	return newLevel; 
}

int Level4::getLevel() { return 4; }

void Level4::setCleared(bool _cleared){
	cleared = _cleared; 
	cleared ? turns = 1 : cleared; 
}

bool Level4::isMakeBrown(){
	return (turns % 6 == 0 && turns) ? true : false; 
}

shared_ptr<Block> Level4::makeBrown(){
	setCleared(true);
	return make_shared<BBlock>(Coordinates{5, 3}); 
}

void Level4::setRandomOff(string _fileName){
	bool restore = random; 
	random = false; 
	fileName = _fileName; 
	try{
		inFile = std::ifstream(fileName); 
		inFile.exceptions(std::ios_base::failbit); 
	} catch (std::ios_base::failure&){
		random = restore; 
		cout << "Could not open input file" << endl; 
	}
}

void Level4::setRandomOn(){
	random = true;  
}

bool Level4::getRandom(){
	return random; 
}
