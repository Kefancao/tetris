#include "TBlock.h"

TBlock::TBlock(Coordinates bottomLeft, bool heavy) 
	: Block{3, 2, heavy} 
{
	positions.emplace_back(bottomLeft.x, bottomLeft.y-1); 
	positions.emplace_back(bottomLeft.x + 1, bottomLeft.y - 1);
	positions.emplace_back(bottomLeft.x + 1, bottomLeft.y);
	positions.emplace_back(bottomLeft.x + 2, bottomLeft.y - 1);
}

char TBlock::getType() const {
	return 'T'; 
}
