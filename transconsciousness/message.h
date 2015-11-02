#ifndef _MESSAGE_H_
#define _MESSAGE_H_

class GameObject;

struct Message
{
	enum Type {
		M_UNKNOWN = 0,
		M_DAMAGE,
		M_PUSHCOMMAND,
		M_DEATH,
		//M_QUERYHABETARGETREQUEST,
		//M_QUERYHABETARGETRESPONSE,
	};

	GameObject* sender;

	Message(GameObject* sender) : sender(sender) {}
	virtual Type getType() const = 0;
};

#endif
