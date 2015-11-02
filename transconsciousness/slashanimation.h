#ifndef _SLASH_ANIMATION_H_
#define _SLASH_ANIMATION_H_
#include "gameobject.h"

class SlashAnimation : public GameObject
{
public:
	float dir;
	int life_time;

	SlashAnimation();
	SlashAnimation(float x, float y, float dir);
	~SlashAnimation();

	Type getType() { return T_SLASHANIMATION; }

	void update();
};

#endif
