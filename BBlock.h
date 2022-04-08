#ifndef __BBLOCK_H__
#define __BBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class BBlock: public Block {
	public:  
		BBlock(Coordinates bottomLeft, bool heavy = false);
		char getType() const override; 
}; 

#endif
