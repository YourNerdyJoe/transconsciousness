#ifndef _GUI_OBJECT_H_
#define _GUI_OBJECT_H_
#include "rect.h"

class GuiObject : public Rect
{
public:
	int tex_id;

	GuiObject();
	GuiObject(float x, float y, float w, float h, int tex_id);

	virtual void onClick(const Vec2 m_pos, int m_button) = 0;
	bool checkClicked(int m_button);

	void render();
};

#endif
