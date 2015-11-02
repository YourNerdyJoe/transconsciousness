#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class GameObject;
struct Message;

class Component
{
protected:
	GameObject* parent;
public:
	inline GameObject* getParent() { return parent; }

	Component(GameObject* parent);
	virtual ~Component();

	enum Type {
		T_UNKNOWN = 0,
		T_STATS,
		T_DEFEATONDELETE,
		T_ANIMATION,
	};

	virtual Type getType() = 0;

	virtual void update();
	virtual void handleMessage(const Message* msg);
	virtual void render();
};

#endif
