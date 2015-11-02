#ifndef _RECT_H_
#define _RECT_H_
#include "vec2.h"

class Rect
{
public:
	Vec2 pos;
	float w, h;

	Vec2 v[4];	//vertices

	Rect();
	Rect(float x, float y, float w, float h);
	~Rect();

	void calculateVertices();
};

#endif
