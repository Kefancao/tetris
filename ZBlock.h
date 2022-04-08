#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class ZBlock: public Block {
	public:  
		ZBlock(Coordinates bottomLeft, bool heavy = false); 
		char getType() const override; 
}; 

#endif 
