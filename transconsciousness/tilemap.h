#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_
#include "vec2.h"

class TileMap
{
	unsigned char* data;
	int width, height;
	int tile_size;

	Vec2* tile_pos_world;
	Vec2* tile_pos_screen;

public:
	TileMap();
	~TileMap();

	bool load(const char* filename);
	bool load(unsigned char* d, int w, int h, int tilesz);

	void draw(const Vec2& offset = Vec2());

	inline unsigned char* getTileData() { return data; }
	inline int getWidth() { return width; }
	inline int getHeight() { return height; }
	inline int getTileSize() { return tile_size; }
	inline const Vec2* getTilePositions() { return tile_pos_world; }
};

#endif
