#include "coordinates.h"

Coordinates::Coordinates(int x, int y) : x{x}, y{y}{}

bool Coordinates::operator==(const Coordinates& other) const{
	return other.x == x && other.y == y; 
}
