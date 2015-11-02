#ifndef _PUSH_COMMAND_MESSAGE_H_
#define _PUSH_COMMAND_MESSAGE_H_
#include "message.h"
#include "commandqueue.h"

struct PushCommandMessage : public Message
{
	Command command;

	Type getType() const { return M_PUSHCOMMAND; }

	PushCommandMessage(GameObject* sender, Command command) : Message(sender), command(Command) {}
}

#endif
