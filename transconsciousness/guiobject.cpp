#include "guiobject.h"
#include "sys.h"

GuiObject::GuiObject() : Rect(), tex_id(-1)
{
}

GuiObject::GuiObject(float x, float y, float w, float h, int tex_id) : Rect(x, y, w, h), tex_id(tex_id)
{
}

bool GuiObject::checkClicked(int m_button)
{
	if(isButtonPressed(m_button))
	{
		float mx = getMousePos().x;
		float my = getMousePos().y;

		if( mx >= v[0].x && mx < v[2].x &&
			my >= v[0].y && my < v[2].y )
		{
			printf("clicked\n");
			onClick(getMousePos(), m_button);
			return true;
		}
	}
	return false;
}

void GuiObject::render()
{
	int frame = 0;
	int frame_w, frame_h;
	SDL_Texture* texture = getTextureData(tex_id, &frame_w, &frame_h);

	float mx = getMousePos().x;
	float my = getMousePos().y;

	if( mx >= v[0].x && mx < v[2].x &&
		my >= v[0].y && my < v[2].y )
	{
		frame = 1;
	}

	SDL_Rect src = {
		0,
		frame * frame_h,
		frame_w,
		frame_h,
	};

	int half_w = w/2, half_h = h/2;
	SDL_Rect dst = {
		(int)pos.x - half_w,
		(int)pos.y - half_h,
		w,
		h,
	};

	SDL_RenderCopy(renderer, texture, &src, &dst);
}
