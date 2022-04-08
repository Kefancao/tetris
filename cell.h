#ifndef __CELL_H__
#define __CELL_H__
#include "subject.h"
#include "coordinates.h"
#include <memory> 

using std::shared_ptr; 

class TextDisplay; 
class Block; 

class Cell: public Subject{
	Coordinates myCoords; 
	shared_ptr<Block> myBlock; 
	bool blind;
	int boardNum;
	bool next;

	public: 
		Cell(int x, int y); 

		virtual void notifyObservers() override; 

		// returns true if myBlock is not null
		bool isOccupied(); 

		// calls myBlock's getType() method
		char getBlockType(); 


		// getters and setters

		void setBlock(shared_ptr<Block> _occupied); 
		shared_ptr<Block> getBlock(); 

		void setBlind(bool _blind);

		int getBoardNum();
		void setBoardNum(int num);

		bool isNext();
		void setNext(bool _next);

		void setCoords(int x, int y);
		int getX() const;
		int getY() const; 
}; 

#endif 
