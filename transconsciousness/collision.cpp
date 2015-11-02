#include "collision.h"

bool checkCollision(Rect& r1, Rect& r2)
{
	if( (r1.v[0].x > r2.v[0].x && r1.v[0].x < r2.v[2].x) ||
		(r1.v[2].x > r2.v[0].x && r1.v[2].x < r2.v[2].x) )
	{
		if( (r1.v[0].y > r2.v[0].y && r1.v[0].y < r2.v[2].y) ||
			(r1.v[2].y > r2.v[0].y && r1.v[2].y < r2.v[2].y) )
		{
			return true;
		}
	}

	return false;
}
