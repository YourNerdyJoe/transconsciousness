#include "animation.h"
#include "gameobject.h"

Animation::Animation(GameObject* parent) : 
Component(parent), max_frames(1), frame_delay(0), frame_delay_count(0)
{
}

Animation::Animation(GameObject* parent, int max_frames, int frame_delay) : 
Component(parent), max_frames(max_frames), frame_delay(frame_delay), frame_delay_count(0)
{
}

Animation::~Animation()
{
}

void Animation::update()
{
	if(frame_delay_count >= frame_delay)
	{
		parent->getSprite().frame++;
		if(parent->getSprite().frame >= max_frames)
		{
			parent->getSprite().frame = 0;
		}
		frame_delay_count = 0;
	}
	else
	{
		frame_delay_count++;
	}
}
