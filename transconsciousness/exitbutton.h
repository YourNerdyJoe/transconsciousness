#ifndef _EXIT_BUTTON_H_
#define _EXIT_BUTTON_H_
#include "guiobject.h"
#include "engine.h"

class ExitButton : public GuiObject
{
public:
	ExitButton() : GuiObject() {}
	ExitButton(float x, float y, float w, float h, int tex_id) : GuiObject(x, y, w, h, tex_id) {}

	void onClick(const Vec2 m_pos, int m_button)
	{
		Engine::setState(Engine::S_EXIT);
	}
};

#endif
