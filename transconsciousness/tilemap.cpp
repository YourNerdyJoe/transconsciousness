#include "tilemap.h"
#include <stdio.h>
#include "isometric.h"
#include "sys.h"

TileMap::TileMap() : data(nullptr), width(0), height(0), tile_size(0), tile_pos_world(nullptr), tile_pos_screen(nullptr)
{
}

TileMap::~TileMap()
{
	printf("delete tilemap\n");
	if(data) delete[] data;
	if(tile_pos_world) delete[] tile_pos_world;
	if(tile_pos_screen) delete[] tile_pos_screen;
}

bool TileMap::load(const char* filename)
{
	FILE* f = fopen(filename, "r");
	if(!f)
	{
		printf("error tilemap %s\n", filename);
		return false;
	}

	printf("tilemap %s\n", filename);

	int w, h;
	fscanf_s(f, "%02X %02X\n", &w, &h);
	printf("%d %d\n", w, h);

	int size = w * h;
	auto d = new unsigned char[size];

	int i;
	for(i = 0; i < size; i++)
	{
		int temp;
		if(!fscanf(f, "%02X", &temp))
		{
			printf("error tile %d\n");
			delete[] d;
			fclose(f);
			return false;
		}
		else
			d[i] = (unsigned char)temp;
	}

	printf("load %d tiles\n", i);

	fclose(f);

	return load(d, w, h, 32);
}

bool TileMap::load(unsigned char* d, int w, int h, int tilesz)
{
	data = d;
	width = w;
	height = h;
	tile_size = tilesz;

	printf("load map data\n");

	int size = w * h;

	if(tile_pos_world) delete[] tile_pos_world;
	if(tile_pos_screen) delete[] tile_pos_screen;

	tile_pos_world = new Vec2[size];
	tile_pos_screen = new Vec2[size];

	Vec2 half_tile((float)tile_size, (float)tile_size/2);

	int i;
	for(i = 0; i < size; i++)
	{
		tile_pos_world[i].setElements(
			(float)(i % width) * tile_size,
			(float)(i / width) * tile_size);

		tile_pos_screen[i] = worldToScreen(tile_pos_world[i]) - half_tile;
	}

	return true;
}

void TileMap::draw(const Vec2& offset)
{
	int frame_w, frame_h;
	SDL_Texture* texture = getTextureData(getTexture("tiles"), &frame_w, &frame_h);
	if(!texture) return;
	int half_tile_size = tile_size / 2;

	int i, size = width * height;
	for(i = 0; i < size; i++)
	{
		SDL_Rect src = {
			1 * frame_w,
			0,
			frame_w,
			frame_h,
		};

		SDL_Rect dst = {
			(int)(tile_pos_screen[i].x - offset.x),
			(int)(tile_pos_screen[i].y - offset.y),
			tile_size*2,
			tile_size,
		};

		SDL_RenderCopy(renderer, texture, &src, &dst);

		//SDL_SetRenderDrawColor(renderer, 0,0,255,255);
		//SDL_RenderDrawRect(renderer, &dst);
		//SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	}
}
