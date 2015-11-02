#ifndef _MOVE_COMMAND_BUTTON_H_
#define _MOVE_COMMAND_BUTTON_H_
#include "guiobject.h"
#include "engine.h"

class MoveCommandButton : public GuiObject
{
public:
	MoveCommandButton() : GuiObject() {}
	MoveCommandButton(float x, float y, float w, float h, int tex_id) : GuiObject(x, y, w, h, tex_id) {}

	void onClick(const Vec2 m_pos, int m_button)
	{
		Engine::setState(Engine::S_PLANMOVE);
	}
};

#endif
