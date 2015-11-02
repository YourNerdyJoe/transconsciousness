#ifndef _CIVILIAN_H_
#define _CIVILIAN_H_
#include "gameobject.h"
#include "sys.h"

class Civilian : public GameObject
{
public:
	Civilian();
	Civilian(float x, float y, int spr_direction);
	~Civilian();

	Type getType() { return T_CIVILIAN; };

	void update();

protected:
	void objectHandleMessage(const Message* msg);
};

#endif
