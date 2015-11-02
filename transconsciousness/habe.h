#ifndef _HABE_H_
#define _HABE_H_
#include "gameobject.h"
#include "stats.h"

class Habe : public GameObject
{
public:
	Habe();
	Habe(float x, float y, int anchor_x, int anchor_y, float w, float h, float spr_w, float spr_h, int tex_id, int max_hp);
	virtual ~Habe();

	Type getType() { return T_HABE; }

	virtual void update() = 0;
	virtual Vec2 plotMovement(int time) = 0;

	void drawPlannedMovement(int time);
	virtual void drawPath() = 0;

	static void drawPlannedMovementAll(int time);
	static void drawPathAll();

protected:
	void objectHandleMessage(const Message* msg);
};

#endif
