#ifndef __IBLOCK_H__
#define __IBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class IBlock: public Block {
	public:  
		IBlock(Coordinates bottomLeft, bool heavy = false);
		char getType() const override; 
}; 

#endif
