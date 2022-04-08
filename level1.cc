#include "level1.h" 
#include "level0.h" 
#include "level2.h" 
#include "blocksList.h"
#include "level.h"
#include "coordinates.h"
#include <random> 
#include <iostream> 

using std::shared_ptr; 
using std::make_shared; 
using std::discrete_distribution; 

Level1::Level1(int seed): Level{seed}{}

shared_ptr<Block> Level1::make(BlockTypes force){
	discrete_distribution<int> probs({0, 1, 1, 2, 2, 2, 2, 2});  
	BlockTypes blockGen = force == BlockTypes::Nothing ? BlockTypes(probs(gen)) : force; 
	return mapChar(blockGen); 
}

// Make <Level1> into <Level1> 
shared_ptr<Level> Level1::increase(){
	shared_ptr<Level2> newLevel = make_shared<Level2>(seed); 
	return newLevel; 
}

// Make <Level0> into <Level1> 
shared_ptr<Level> Level1::decrease(){
	shared_ptr<Level0> newLevel = make_shared<Level0>(seed); 
	return newLevel; 
}

int Level1::getLevel() { return 1; }
