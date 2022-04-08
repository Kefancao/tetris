#include "cell.h" 
#include "block.h"
#include "textdisplay.h"
#include <iostream> 

using std::shared_ptr; 

Cell::Cell(int x, int y) :
	myCoords{Coordinates{x, y}}, myBlock{nullptr}, blind{false}
{}

void Cell::setBlock(shared_ptr<Block> _occupied) {
	myBlock = _occupied; 
}

shared_ptr<Block> Cell::getBlock() {
	return myBlock; 
}

void Cell::notifyObservers() {
	for (auto n : observers){
		n->notify(*this); 
	}
}

bool Cell::isOccupied() {
	return myBlock ? true : false ; 
}

char Cell::getBlockType() {
	if (blind) return '?';
	else if (myBlock) return myBlock->getType(); 
	else return ' ';
}

void Cell::setBlind(bool _blind) {
	blind = _blind;
	notifyObservers();
}

int Cell::getBoardNum() { return boardNum; }
void Cell::setBoardNum(int num) { boardNum = num; }

bool Cell::isNext() { return next; }
void Cell::setNext(bool _next) { next = _next; }

void Cell::setCoords(int x, int y) {
	myCoords.x = x;
	myCoords.y = y;
}

int Cell::getX() const { return myCoords.x; }

int Cell::getY() const {return myCoords.y; }
