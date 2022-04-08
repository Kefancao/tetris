#ifndef __LBLOCK_H__
#define __LBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class LBlock: public Block {
	public:  
		LBlock(Coordinates bottomLeft, bool heavy = false); 
		char getType() const override; 
}; 

#endif
