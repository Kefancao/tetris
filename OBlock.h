#ifndef __OBLOCK_H__
#define __OBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class OBlock: public Block {
	public:  
		OBlock(Coordinates bottomLeft, bool heavy = false); 
		char getType() const override; 
}; 

#endif 
