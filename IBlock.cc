#include "IBlock.h"

IBlock::IBlock(Coordinates bottomLeft, bool heavy) 
	: Block{4, 1, heavy}
{
	positions.emplace_back(bottomLeft.x, bottomLeft.y); 
	positions.emplace_back(bottomLeft.x + 1, bottomLeft.y);
	positions.emplace_back(bottomLeft.x + 2, bottomLeft.y);
	positions.emplace_back(bottomLeft.x + 3, bottomLeft.y);
}

char IBlock::getType() const {
	return 'I'; 
}
