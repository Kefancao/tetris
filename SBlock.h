#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class SBlock: public Block {
	public:  
		SBlock(Coordinates bottomLeft, bool heavy = false); 
		char getType() const override; 
}; 

#endif
