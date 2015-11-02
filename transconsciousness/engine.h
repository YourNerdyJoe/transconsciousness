#ifndef _ENGINE_H_
#define _ENGINE_H_
#include "tilemap.h"
#include "level.h"

namespace Engine
{
	enum State {
		S_MAINMENU,
		S_STARTLEVEL,
		S_LEVELCOMPLETE,
		S_PLAN,
		S_PLANMOVE,
		S_PLANSLASH,
		S_PLANSHOOT,
		S_RUN,
		S_WAIT,
		S_DEFEAT,
		S_VICTORY,
		S_EXIT,
	};

	extern TileMap* cur_map;

	void initialize(State s);

	void setState(State s);
	State getState();

	void setLevelArray(Level* lv_arr, int size);

	bool mainLoop();
}

#endif
