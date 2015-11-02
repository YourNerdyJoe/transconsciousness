#include "sprite.h"
#include "isometric.h"
#include "sys.h"

Sprite::Sprite() : Rect(), world_pos(), tex_id(-1), anchor_x(0), anchor_y(0), animation(0), frame(0), dir(0)
{
}

Sprite::Sprite(float world_x, float world_y, int anchor_x, int anchor_y, float w, float h, int tex_id) : world_pos(world_x, world_y), tex_id(tex_id), anchor_x(anchor_x), anchor_y(anchor_y), animation(0), frame(0), dir(0)
{
	this->w = w;
	this->h = h;

	spriteCalculateVertices();
}

Sprite::~Sprite()
{
}

void Sprite::spriteCalculateVertices()
{
	pos = worldToScreen(world_pos);
	v[0].setElements(pos.x-anchor_x,	pos.y-anchor_y);
	v[1].setElements(pos.x-anchor_x+w,	pos.y-anchor_y);
	v[2].setElements(pos.x-anchor_x+w,	pos.y-anchor_y+h);
	v[3].setElements(pos.x-anchor_x,	pos.y-anchor_y+h);
}

void Sprite::draw()
{
	int tex_w, tex_h;
	SDL_Texture* texture = getTextureData(tex_id, &tex_w, &tex_h);

	SDL_Rect src = {
		tex_w*frame,
		tex_h*animation,
		tex_w,
		tex_h,
	};

	SDL_Rect dst = {
		(int)v[0].x - getCamera().x,
		(int)v[0].y - getCamera().y,
		(int)w,
		(int)h,
	};

	//SDL_SetRenderDrawColor(renderer, 0,0,255,255);
	//SDL_RenderDrawRect(renderer, &dst);
	//SDL_SetRenderDrawColor(renderer, 255,255,255,255);

	if(dir == 0)
	{
		SDL_RenderCopy(renderer, texture, &src, &dst);
	}
	else
	{
		SDL_Point point = { anchor_x, anchor_y };
		SDL_RenderCopyEx(renderer, texture, &src, &dst, dir, &point, SDL_FLIP_NONE);
	}
}
