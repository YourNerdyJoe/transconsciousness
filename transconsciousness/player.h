#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "gameobject.h"
#include "commandqueue.h"

class Player : public GameObject
{
public:
	CommandQueue command_queue;

	Player();
	Player(float x, float y);
	~Player();

	Type getType() { return T_PLAYER; }

	void update();
protected:
	void objectHandleMessage(const Message* msg);
};

#endif
