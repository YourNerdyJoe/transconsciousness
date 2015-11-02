#include "isometric.h"

Vec2 worldToScreen(const Vec2& v)
{
	return Vec2(v.x - v.y, (v.x + v.y)/2.0f);
}

Vec2 screenToWorld(const Vec2& v)
{
	return Vec2((v.x+2.0f*v.y)/2.0f, (2.0f*v.y-v.x)/2.0f);
}
