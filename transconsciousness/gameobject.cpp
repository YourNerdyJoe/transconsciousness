#include "gameobject.h"
#include "sprite.h"
#include "sys.h"

std::list<GameObject*> GameObject::obj_list;
std::list<GameObject*> GameObject::trash_list;

void GameObject::addToList()
{
	obj_list.push_back(this);
}

void GameObject::removeFromList()
{
	obj_list.remove(this);
}


GameObject::GameObject() : Rect(), spr(), is_static(false), is_solid(false)
{
	addToList();
}

GameObject::GameObject(float x, float y, int anchor_x, int anchor_y, float w, float h, float spr_w, float spr_h, int tex_id, bool is_static, bool is_solid) : 
Rect(x, y, w, h), spr(x, y, anchor_x, anchor_y, spr_w, spr_h, tex_id), is_static(is_static), is_solid(is_solid)
{
	addToList();
}

GameObject::~GameObject()
{
	//removeFromList();
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		delete it->second;
	}
	printf("delete obj\n");
}

void GameObject::render()
{
	spr.world_pos = pos;
	spr.spriteCalculateVertices();

	pushSprite(spr);
}

void GameObject::markTrash()
{
	trash_list.push_back(this);
}

void GameObject::handleMessage(const Message* msg)
{
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		it->second->handleMessage(msg);
	}

	objectHandleMessage(msg);
}

void GameObject::addComponent(Component* c)
{
	if(!c) return;

	auto type = c->getType();

	auto it = comp_list.find(type);
	if(it != comp_list.end())
	{
		delete it->second;
	}

	comp_list[type] = c;
}

Component* GameObject::getComponent(Component::Type type)
{
	auto it = comp_list.find(type);
	if(it == comp_list.end())
	{
		return nullptr;
	}

	return it->second;
}


//Global

void GameObject::updateAll()
{
	for(auto it = obj_list.begin(); it != obj_list.end(); it++)
	{
		GameObject* o = *it;
		o->update();

		//update components
		for(auto j = o->comp_list.begin(); j != o->comp_list.end(); j++)
		{
			j->second->update();
		}
	}
}

void GameObject::renderAll()
{
	for(auto it = obj_list.begin(); it != obj_list.end(); it++)
	{
		GameObject* o = *it;

		//Component render
		for(auto j = o->comp_list.begin(); j != o->comp_list.end(); j++)
		{
			j->second->render();
		}

		o->render();
	}
}

void GameObject::cleanUp()
{
	for(auto i = trash_list.begin(); i != trash_list.end(); i++)
	{
		for(auto j = obj_list.begin(); j != obj_list.end(); j++)
		{
			if(*i == *j)
			{
				delete *j;
				obj_list.erase(j);
				break;
			}
		}
	}
	trash_list.clear();
}

void GameObject::deleteAll()
{
	for(auto it = obj_list.begin(); it != obj_list.end(); it++)
	{
		delete (*it);
	}
	obj_list.clear();
}

void GameObject::broadcastMessage(const Message* msg)
{
	for(auto it = obj_list.begin(); it != obj_list.end(); it++)
	{
		(*it)->handleMessage(msg);
	}
}

void GameObject::broadcastMessageType(const Message* msg, Type type)
{
	for(auto it = obj_list.begin(); it != obj_list.end(); it++)
	{
		if((*it)->getType() == type)
			(*it)->handleMessage(msg);
	}
}

GameObject* GameObject::getFirstGameObjectOfType(Type type)
{
	for(auto it = obj_list.begin(); it != obj_list.end(); it++)
	{
		if((*it)->getType() == type)
			return *it;
	}
	return nullptr;
}
