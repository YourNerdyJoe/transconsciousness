#include "civilian.h"
#include "message.h"
#include "engine.h"
#include "particlesystem.h"
#include "defeatondelete.h"

Civilian::Civilian() : GameObject(0, 0, 31, 48, 14, 14, 64, 64, getTexture("hard_drive"), true, false)
{
	spr.animation = 0;
}

Civilian::Civilian(float x, float y, int spr_direction) : GameObject(x, y, 31, 48, 16, 16, 64, 64, getTexture("hard_drive"), true, false)
{
	spr.animation = spr_direction;
}

Civilian::~Civilian()
{
}

void Civilian::update()
{
}

void Civilian::objectHandleMessage(const Message* msg)
{
	if(msg->getType() == Message::M_DEATH)
	{
		//Engine::setState(Engine::S_DEFEAT);
		markTrash();

		ParticleSystem* part_sys = new ParticleSystem(pos.x, pos.y, 2, 2, 2, 2, 200, 100, 205, 245, 5, 0xFF, 0x0, 0x0, 0xFF);
		part_sys->addComponent(new DefeatOnDelete(part_sys));

		Engine::setState(Engine::S_WAIT);
	}
}
