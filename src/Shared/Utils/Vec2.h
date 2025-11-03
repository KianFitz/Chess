#include <cstdint>
#ifndef __H_VEC2
#define __H_VEC2

class Vec2 {

public:
	Vec2(float aX, float aY) : x(aX), y(aY) {};
	Vec2() : x(0), y(0) {};

	float x;
	float y;

};


#endif