#ifndef _DONE_PLANNING_BUTTON_H_
#define _DONE_PLANNING_BUTTON_H_
#include "guiobject.h"
#include "engine.h"

class DonePlanningButton : public GuiObject
{
public:
	DonePlanningButton() : GuiObject() {}
	DonePlanningButton(float x, float y, float w, float h, int tex_id) : GuiObject(x, y, w, h, tex_id) {}

	void onClick(const Vec2 m_pos, int m_button)
	{
		Engine::setState(Engine::S_RUN);
	}
};

#endif
