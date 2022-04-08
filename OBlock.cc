#include "OBlock.h"

OBlock::OBlock(Coordinates bottomLeft, bool heavy) 
	: Block{2, 2, heavy} 
{
	positions.emplace_back(bottomLeft.x, bottomLeft.y); 
	positions.emplace_back(bottomLeft.x, bottomLeft.y - 1);
	positions.emplace_back(bottomLeft.x + 1, bottomLeft.y);
	positions.emplace_back(bottomLeft.x + 1, bottomLeft.y-1);
}

char OBlock::getType() const {
	return 'O'; 
}
