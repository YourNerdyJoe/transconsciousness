#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_
#include <math.h>

struct Vec2
{
	float x, y;

	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}

	inline void setElements(float x, float y) { this->x = x; this->y = y;  }

	inline Vec2 operator+(const Vec2& rhs) const { return Vec2(x+rhs.x, y+rhs.y); }
	inline Vec2 operator-(const Vec2& rhs) const { return Vec2(x-rhs.x, y-rhs.y); }
	inline Vec2 operator-() const { return Vec2(-x, -y); }
	inline Vec2 operator*(float rhs) const	{ return Vec2(x*rhs, y*rhs); }

	inline Vec2& operator+=(const Vec2& rhs) { x+=rhs.x; y+=rhs.y; return *this; }
	inline Vec2& operator-=(const Vec2& rhs) { x-=rhs.x; y-=rhs.y; return *this; }
	inline Vec2& operator*=(float rhs) { x*=rhs; y*=rhs; return *this; }

	inline bool operator==(const Vec2& rhs) { return (x == rhs.x && y == rhs.y); }

	float getMagnitude()
	{ return sqrt( (x*x) + (y*y) ); }

	float getDirection()
	{ return atan2(y, x); }

	Vec2 getNormalized() {
		if(x == 0 && y == 0) return Vec2(0,0);
		float len = getMagnitude();
		return Vec2(x/len, y/len);	
	}

	float dot(Vec2& v) {
		 return (x * v.x) + (y * v.y);
	}

	void clamp(float length) {
		float len = getMagnitude();
		if(len > length) {
			float d = length/len;
			x *= d;
			y *= d;
		}
	}
};

#endif
