#ifndef _STATS_H_
#define _STATS_H_
#include "component.h"

struct Message;

struct Stats : public Component
{
	int hp, max_hp;

	Type getType() { return T_STATS; }

	Stats(GameObject* parent) : Component(parent) {}
	Stats(GameObject* parent, int hp, int max_hp) : Component(parent), hp(hp), max_hp(max_hp) {}

	int damage(int amount);
	int heal(int amount);

	void handleMessage(const Message* msg);

	void render();
};

#endif
