#ifndef __TBLOCK_H__
#define __TBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class TBlock: public Block {
	public:  
		TBlock(Coordinates bottomLeft, bool heavy = false); 
		char getType() const override; 
}; 

#endif 
