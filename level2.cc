#include "level1.h" 
#include "level2.h" 
#include "level3.h" 
#include "blocksList.h"
#include "level.h"
#include "coordinates.h"
#include <random> 
#include <iostream> 

using std::shared_ptr; 
using std::make_shared; 
using std::discrete_distribution; 

Level2::Level2(int seed): Level{seed}{}

shared_ptr<Block> Level2::make(BlockTypes force){
	discrete_distribution<int> probs({0, 1, 1, 1, 1, 1, 1, 1});  
	BlockTypes blockGen = force == BlockTypes::Nothing ? BlockTypes(probs(gen)) : force; 
	return mapChar(blockGen); 
}

// Make <Level0> into <Level1> 
shared_ptr<Level> Level2::increase(){
	shared_ptr<Level3> newLevel = make_shared<Level3>(seed); 
	return newLevel; 
}

// Make <Level0> into <Level1> 
shared_ptr<Level> Level2::decrease(){
	shared_ptr<Level1> newLevel = make_shared<Level1>(seed); 
	return newLevel; 
}

int Level2::getLevel() { return 2; }
