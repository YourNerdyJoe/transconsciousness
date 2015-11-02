#include "stats.h"
#include "damagemessage.h"
#include "sys.h"
#include "deathmessage.h"
#include "gameobject.h"
#include "isometric.h"

int Stats::damage(int amount)
{
	hp -= amount;
	if(hp < 0) {
		amount += hp;
		hp = 0;
	}
	return amount;
}

int Stats::heal(int amount)
{
	hp += amount;
	if(hp > max_hp) {
		amount -= hp - max_hp;
		hp = max_hp;
	}
	return amount;
}

void Stats::handleMessage(const Message* msg)
{
	if(msg->getType() == Message::M_DAMAGE)
	{
		auto dm = (DamageMessage*)msg;
		printf("damage %d\n", damage(dm->amount));

		if(hp <= 0)
		{
			parent->handleMessage(&DeathMessage(parent));
		}
	}
}

void Stats::render()
{
	Vec2 screen = worldToScreen(parent->pos) - getCamera();

	SDL_Rect dst = {
		screen.x - 4,
		screen.y + 8,
		hp * 4,
		2,
	};

	switch(hp)
	{
	case 1:
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		break;
	case 2:
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		break;
	default:
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		break;
	}

	SDL_RenderDrawRect(renderer, &dst);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
