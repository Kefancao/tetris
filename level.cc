#include "level.h" 
#include <random>

using std::make_shared; 

Level::Level(int seed): seed{seed}{
	if (!seed){
		std::random_device rd; 
		gen.seed(rd());
	}
	else gen.seed(seed);
}

shared_ptr<Block> Level::mapChar(BlockTypes type, bool heavy){
	Coordinates init{0,3};
	switch (type){
		// SBlock 
		case BlockTypes::S: 
			return make_shared<SBlock>(init, heavy);
		// ZBlock
		case BlockTypes::Z: 
			return make_shared<ZBlock>(init, heavy);
		// TBlock 
		case BlockTypes::T: 
			return make_shared<TBlock>(init, heavy);
		// OBlock 
		case BlockTypes::O: 
			return make_shared<OBlock>(init, heavy);
		// JBlock 
		case BlockTypes::J: 
			return make_shared<JBlock>(init, heavy);
		// LBlock
		case BlockTypes::L: 
			return make_shared<LBlock>(init, heavy);
		// IBlock
		case BlockTypes::I: 
			return make_shared<IBlock>(init, heavy); 
		default: 
			return nullptr; 
	}
}

BlockTypes Level::charToBT(char c) {
	switch (c) {
		case 'I': return BlockTypes::I; 
		case 'J': return BlockTypes::J;
		case 'L': return BlockTypes::L;
		case 'O': return BlockTypes::O;
		case 'S': return BlockTypes::S;
		case 'T': return BlockTypes::T;
		case 'Z': return BlockTypes::Z;
		default: return BlockTypes::Nothing; 
	}
}
