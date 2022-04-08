#include "BBlock.h"

BBlock::BBlock(Coordinates bottomLeft, bool heavy) 
	: Block{1, 1, heavy}
{
	positions.emplace_back(bottomLeft.x, bottomLeft.y); 
}

char BBlock::getType() const {
	return '*'; 
}
