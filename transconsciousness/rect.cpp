#include "rect.h"

Rect::Rect() : pos(0, 0), w(16), h(16)
{
	calculateVertices();
}

Rect::Rect(float x, float y, float w, float h) : pos(x, y), w(w), h(h)
{
	calculateVertices();
}

Rect::~Rect()
{
}

void Rect::calculateVertices()
{
	float hw = w/2,
		hh = h/2;

	v[0].setElements(pos.x-hw, pos.y-hh);
	v[1].setElements(pos.x+hw, pos.y-hh);
	v[2].setElements(pos.x+hw, pos.y+hh);
	v[3].setElements(pos.x-hw, pos.y+hh);
}
