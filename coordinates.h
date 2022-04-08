#ifndef __COORDINATES_H__
#define __COORDINATES_H__

struct Coordinates{
	int x, y;
	Coordinates(int x, int y); 
	bool operator==(const Coordinates& other) const; 
}; 

#endif 
