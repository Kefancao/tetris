#ifndef __JBLOCK_H__
#define __JBLOCK_H__
#include "block.h" 
#include "coordinates.h"

class JBlock: public Block {
	public:  
		JBlock(Coordinates bottomLeft, bool heavy = false); 
		char getType() const override; 
}; 

#endif 
