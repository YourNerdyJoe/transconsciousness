#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "component.h"

class Animation : public Component
{
public:
	int max_frames;
	int frame_delay, frame_delay_count;

	Animation(GameObject* parent);
	Animation(GameObject* parent, int max_frames, int frame_delay);
	~Animation();

	Type getType() { return T_ANIMATION; }

	void update();
};

#endif
