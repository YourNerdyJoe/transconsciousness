#ifndef _DAMAGE_MESSAGE_H_
#define _DAMAGE_MESSAGE_H_
#include "message.h"

struct DamageMessage : public Message
{
	int amount;

	Type getType() const { return M_DAMAGE; }

	DamageMessage(GameObject* sender, int amount) : Message(sender), amount(amount) {}
	~DamageMessage() {}
};

#endif
