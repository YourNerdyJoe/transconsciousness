#ifndef _KILL_CIVIAN_MESSAGE_H_
#define _KILL_CIVIAN_MESSAGE_H_
#include "message.h"

struct DeathMessage : public Message
{
	Type getType() const { return M_DEATH; }

	DeathMessage(GameObject* sender) : Message(sender) {}
};

#endif
