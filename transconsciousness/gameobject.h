#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_
#include "rect.h"
#include <list>
#include <map>
#include "sprite.h"
#include "component.h"

struct Message;

class GameObject : public Rect
{
protected:
	Sprite spr;
	std::map<Component::Type, Component*> comp_list;

	static std::list<GameObject*> obj_list;
	static std::list<GameObject*> trash_list;
	void addToList();
	void removeFromList();

	virtual void objectHandleMessage(const Message* msg) {}

public:
	bool is_static, is_solid;

	GameObject();
	GameObject(float x, float y, int anchor_x, int anchor_y, float w, float h, float spr_w, float spr_h, int tex_id, bool is_static, bool is_solid);
	virtual ~GameObject();

	enum Type {
		T_UNKNOWN = 0,
		T_PLAYER,
		T_HABE,
		T_BLOCK,
		T_CIVILIAN,
		T_PARTICLES,
		T_SLASHANIMATION,
	};

	virtual Type getType() = 0;

	virtual void update() = 0;
	void handleMessage(const Message* msg);

	void render();

	void markTrash();

	void addComponent(Component* c);
	Component* getComponent(Component::Type type);

	inline Sprite& getSprite() { return spr; }

	//Global
	static void updateAll();
	static void renderAll();
	static void cleanUp();
	static void deleteAll();
	static void broadcastMessage(const Message* msg);
	static void broadcastMessageType(const Message* msg, Type type);

	static GameObject* getFirstGameObjectOfType(Type type);
	static inline std::list<GameObject*>::iterator getListBegin() { return obj_list.begin(); }
	static inline std::list<GameObject*>::iterator getListEnd() { return obj_list.end(); }
};

#endif
