#include "habe.h"
#include "damagemessage.h"
#include "isometric.h"
#include "particlesystem.h"
#include "animation.h"

Habe::Habe() : GameObject()
{
	is_static = false;
	is_solid = false;

	addComponent(new Stats(this));
}

Habe::Habe(float x, float y, int anchor_x, int anchor_y, float w, float h, float spr_w, float spr_h, int tex_id, int max_hp) : GameObject(x, y, anchor_x, anchor_y, w, h, spr_w, spr_h, tex_id, false, false)
{
	addComponent(new Stats(this, max_hp, max_hp));
	addComponent(new Animation(this, 4, 4));
}

Habe::~Habe()
{
}

void Habe::drawPlannedMovement(int time)
{
	int frame_w, frame_h;
	SDL_Texture* texture = getTextureData(getTexture("movement"), &frame_w, &frame_h);

	//get future position
	Vec2 screen = worldToScreen(plotMovement(time)) - getCamera() - Vec2(16, 8);

	SDL_Rect src = {
		0, 0,
		frame_w, frame_h,
	};

	SDL_Rect dst = {
		(int)screen.x, (int)screen.y,
		32, 16,
	};

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Habe::drawPlannedMovementAll(int time)
{
	for(auto it = GameObject::getListBegin(); it != GameObject::getListEnd(); it++)
	{
		if((*it)->getType() == GameObject::T_HABE)
		{
			Habe* h = (Habe*)*it;
			h->drawPlannedMovement(time);
		}
	}
}

void Habe::drawPathAll()
{
	
	for(auto it = GameObject::getListBegin(); it != GameObject::getListEnd(); it++)
	{
		if((*it)->getType() == GameObject::T_HABE)
		{
			Habe* h = (Habe*)*it;
			h->drawPath();
		}
	}
}

void Habe::objectHandleMessage(const Message* msg)
{
	if(msg->getType() == Message::M_DEATH)
	{
		markTrash();
		ParticleSystem* part_sys = new ParticleSystem(pos.x, pos.y, 2, 2, 2, 2, 150, 100, 205, 245, 7, 0xFF, 0x0, 0x0, 0xFF);

		playSound("good_explosion");
	}
}
