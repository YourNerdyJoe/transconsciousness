#ifndef _STATE_BUTTON_H_
#define _STATE_BUTTON_H_
#include "guiobject.h"
#include "engine.h"

struct StateButton : public GuiObject
{
	Engine::State state;

	StateButton(Engine::State state) : GuiObject(), state(state) {}
	StateButton(float x, float y, float w, float h, int tex_id, Engine::State state) : GuiObject(x, y, w, h, tex_id), state(state) {}

	void onClick(const Vec2 m_pos, int m_button)
	{
		Engine::setState(state);
	}
};

#endif
