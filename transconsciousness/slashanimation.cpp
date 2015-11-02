#include "slashanimation.h"
#include "animation.h"
#include "commandqueue.h"

SlashAnimation::SlashAnimation() : GameObject(0, 0, 64, 64, 128, 128, 128, 128, getTexture("slash"), false, false), dir(0)
{
	addComponent(new Animation(this, 5, 2));
	life_time = command_time_execute[Command::C_SLASH] - 1;
}

SlashAnimation::SlashAnimation(float x, float y, float dir) : GameObject(x, y, 64, 64, 128, 128, 128, 128, getTexture("slash"), false, false), dir(dir)
{
	addComponent(new Animation(this, 5, 2));
	life_time = command_time_execute[Command::C_SLASH] - 1;
	spr.dir = dir;
}

SlashAnimation::~SlashAnimation()
{
}

void SlashAnimation::update()
{
	Animation* anim = (Animation*)getComponent(Component::T_ANIMATION);
	//stay on last frame
	if(spr.frame == anim->max_frames-1)
	{
		anim->frame_delay_count = 0;
	}

	life_time--;
	if(life_time <= 0) markTrash();
}
