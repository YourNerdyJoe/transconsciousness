#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "sys.h"
#include "rect.h"

class Sprite : public Rect
{
public:
	Vec2 world_pos;
	int anchor_x, anchor_y;
	int tex_id;
	int animation, frame;
	float dir;

	Sprite();
	Sprite(float world_x, float world_y, int anchor_x, int anchor_y, float w, float h, int tex_id);
	~Sprite();

	void spriteCalculateVertices();
	virtual void draw();
};

#endif
