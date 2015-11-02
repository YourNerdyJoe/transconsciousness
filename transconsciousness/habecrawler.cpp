#include "habecrawler.h"
#include "sys.h"
#include "deathmessage.h"
#include "isometric.h"

HabeCrawler::HabeCrawler() : Habe(0, 0, 31, 48, 32, 32, 64, 64, getTexture("habe_crawler"), 3), target(nullptr)
{
}

HabeCrawler::HabeCrawler(float x, float y, GameObject* target) : Habe(x, y, 31, 48, 32, 32, 64, 64, getTexture("habe_crawler"), 3), target(target)
{
	Vec2 offset = target->pos - pos;
	spr.animation = radianToSpriteDirection(offset.getDirection());
}

HabeCrawler::~HabeCrawler()
{
}

#define CRAWLER_MAX_SPEED 2

void HabeCrawler::update()
{
	if(!target) return;

	Vec2 offset = target->pos - pos;
	offset = offset.getNormalized() * CRAWLER_MAX_SPEED;
	pos += offset;

	spr.animation = radianToSpriteDirection(offset.getDirection());

	//Vec2 pos_tile, target_tile;
	//convTilePos(pos, 32, &pos_tile);
	//convTilePos(target->pos, 32, &target_tile);

	//if(pos_tile == target_tile)
	if((target->pos - pos).getMagnitude() < target->w)
	{
		target->handleMessage(&DeathMessage(this));
		target = nullptr;
	}
}

Vec2 HabeCrawler::plotMovement(int time)
{
	if(!target) return pos;

	Vec2 offset = target->pos - pos;
	float target_distance = offset.getMagnitude();
	float travel_distance = CRAWLER_MAX_SPEED * time;

	//shorter one
	float distance = (target_distance < travel_distance) ? target_distance : travel_distance;

	offset = offset.getNormalized() * distance;

	return pos + offset;
}

void HabeCrawler::drawPath()
{
	if(target)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		Vec2 p1 = worldToScreen(pos) - getCamera();
		Vec2 p2 = worldToScreen(target->pos) - getCamera();
	
		SDL_RenderDrawLine(renderer, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
}

//void HabeCrawler::handleMessage(const Message* msg)
//{
	//stats.handleMessage(msg);
//}
