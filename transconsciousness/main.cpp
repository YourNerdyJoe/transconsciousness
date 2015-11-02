#include "sys.h"
#include "sprite.h"
#include "tilemap.h"
#include "isometric.h"
#include "gameobject.h"
#include "player.h"
#include "engine.h"
#include "habecrawler.h"
#include "civilian.h"
#include "damagemessage.h"
#include "leveldata.h"

/*struct TestObj : public GameObject
{
	Type getType() { return T_BLOCK; }
	void update() {}
	void objectHandleMessage(const Message* msg) {}

	TestObj(float x, float y, int anchor_x, int anchor_y, float w, float h, float spr_w, float spr_h, int tex_id, bool is_static, bool is_solid):
	GameObject(x, y, anchor_x, anchor_y, w, h, spr_w, spr_h, tex_id, is_static, is_solid){}
};*/

int main(int argc, char* argv[])
{
	if(!initialize(argc, argv)) {
		return 1;
	}

	loadTexture("tiles", 32, 16);
	loadTexture("habe_crawler", 32, 32);
	loadTexture("target", 16, 8);
	loadTexture("movement", 16, 8);
	loadTexture("move_button", 96, 32);
	loadTexture("slash_button", 96, 32);
	loadTexture("shoot_button", 96, 32);
	loadTexture("done_button", 96, 32);
	loadTexture("hard_drive", 32, 32);
	loadTexture("title_screen",640,480);
	loadTexture("start_button", 96, 32);
	loadTexture("exit_button", 96, 32);
	loadTexture("slash", 64, 64);
	loadTexture("death", 640, 480);
	loadTexture("defeat", 640, 480);
	loadTexture("retry_button", 96, 32);
	loadTexture("menu_button", 96, 32);
	loadTexture("habe_flier", 32, 32);
	loadTexture("victory", 640, 480);

	loadSound("slash");
	loadSound("shoot");
	loadSound("good_explosion");
	loadSound("bad_explosion");

	loadMusic("transconsciousness");

	playMusic("transconsciousness");

	TileMap map;
	map.load("testlevel.txt");

	getCamera().setElements(-SCREEN_WIDTH/2, 0);

	Engine::initialize(Engine::S_MAINMENU);
	Engine::cur_map = &map;
	Engine::setLevelArray(level_array, NUM_OF_LEVELS);

	int x = 0, y = 0;
	bool quit = false;
	while(!quit)
	{
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
		{
			switch(ev.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}

		//update
		updateInput();

		//render
		clearScreen();

		if(!Engine::mainLoop()) quit = true;

		flipScreen();

		GameObject::cleanUp();

		updateMusic();
	}

	GameObject::deleteAll();
	shutDown();
	return 0;
}
