#include "block.h" 

Block::Block(int width, int height, bool heavy) 
	: width{width}, height{height}, heavy{heavy} {}

void Block::left() {
	for (auto& p : positions) --p.x;
}

void Block::right() {
	for (auto& p : positions) ++p.x;
}

Coordinates Block::getBottomLeft() {
	int maxY = positions[0].y; 
	int minX = positions[0].x; 
	for (auto p : positions) {
		if (p.y > maxY) maxY = p.y; 
		if (p.x < minX) minX = p.x; 
	}
	return Coordinates{minX, maxY}; 
}

void Block::clockwise() {
	Coordinates oldBottom = getBottomLeft();
	for (auto& p : positions) {
		p.x -= oldBottom.x; 
		p.y -= oldBottom.y; 
		int newX = -p.y;
		int newY = p.x;
		p.x = newX + oldBottom.x;  
		p.y = newY + oldBottom.y;
	}
	Coordinates newBottom = getBottomLeft(); 
	Coordinates difference{newBottom.x - oldBottom.x, newBottom.y - oldBottom.y}; 
	for (auto& p : positions){
		p.x -= difference.x; 
		p.y -= difference.y; 
	}
	int newHeight = width;
	width = height;
	height = newHeight;
}

void Block::counterclockwise() {
	for (int i = 0; i < 3; ++i) clockwise(); 
}

void Block::down() { 
	for (auto& p : positions) p.y++; 
}

void Block::up() {
	for (auto& p : positions) p.y--; 
}

std::vector<Coordinates> Block::getPositions() const { return positions; }

bool Block::isHeavy() const { return heavy; }

void Block::makeHeavy() { heavy = true; }

int Block::getLevel() const { return level; }

void Block::setLevel(int _level) { level = _level; }
