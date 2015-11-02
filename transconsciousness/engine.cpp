#include "engine.h"
#include "sys.h"
#include "gameobject.h"
#include "player.h"
#include "isometric.h"
#include "commandqueue.h"
#include "movecommandbutton.h"
#include "slashcommandbutton.h"
#include "shootcommandbutton.h"
#include "doneplanningbutton.h"
#include "habe.h"
#include "startbutton.h"
#include "exitbutton.h"
#include "statebutton.h"

namespace Engine
{
	TileMap* cur_map = nullptr;

	static State state, next_state;

	void initialize(State s)
	{
		state = next_state = s;
	}

	void setState(State s)
	{
		next_state = s;
		printf("state %d\n", s);
	}

	static Level* levels = nullptr;
	static int level_count = 0;
	static int cur_level_idx = 0;

	State getState()
	{
		return state;
	}

	void setLevelArray(Level* lv_arr, int size)
	{
		levels = lv_arr;
		level_count = size;
		cur_level_idx = 0;
	}

	static inline void drawMap()
	{
		if(cur_map) cur_map->draw(getCamera());
	}

	void mainMenu()
	{
		//start and exit buttons
		cur_level_idx = 0;
		
		StartButton start_b(SCREEN_WIDTH/2, 300, 96, 32, getTexture("start_button"));
		ExitButton exit_b(SCREEN_WIDTH/2, 350, 96, 32, getTexture("exit_button"));

		start_b.checkClicked(SDL_BUTTON_LMASK);
		exit_b.checkClicked(SDL_BUTTON_LMASK);

		int frame_w, frame_h;
		SDL_Texture* texture = getTextureData(getTexture("title_screen"), &frame_w, &frame_h);

		SDL_Rect src = {
			0, 0,
			640, 480,
		};

		SDL_RenderCopy(renderer, texture, &src, &src);

		start_b.render();
		exit_b.render();
	}

	void startLevel()
	{
		levels[cur_level_idx].alloc();
		setState(S_PLAN);
	}

	void levelComplete()
	{
		GameObject::deleteAll();

		cur_level_idx++;
		if(cur_level_idx >= level_count)
		{
			setState(S_VICTORY);
			return;
		}

		setState(S_STARTLEVEL);
	}

	void defeat(int tex)
	{
		GameObject::deleteAll();

		StateButton retry_b(SCREEN_WIDTH/2, 300, 96, 32, getTexture("retry_button"), S_STARTLEVEL);
		StateButton menu_b(SCREEN_WIDTH/2, 350, 96, 32, getTexture("menu_button"), S_MAINMENU);

		retry_b.checkClicked(SDL_BUTTON_LMASK);
		menu_b.checkClicked(SDL_BUTTON_LMASK);

		int frame_w, frame_h;
		SDL_Texture* texture = getTextureData(tex, &frame_w, &frame_h);

		SDL_Rect src = {
			0, 0,
			640, 480,
		};

		SDL_RenderCopy(renderer, texture, &src, &src);

		retry_b.render();
		menu_b.render();
	}

	void win()
	{
		GameObject::deleteAll();

		StateButton menu_b(SCREEN_WIDTH/2, 350, 96, 32, getTexture("menu_button"), S_MAINMENU);

		menu_b.checkClicked(SDL_BUTTON_LMASK);

		int frame_w, frame_h;
		SDL_Texture* texture = getTextureData(getTexture("victory"), &frame_w, &frame_h);

		SDL_Rect src = {
			0, 0,
			640, 480,
		};

		SDL_RenderCopy(renderer, texture, &src, &src);

		menu_b.render();
	}

	void planActionPlan()
	{
		Player* player = (Player*)GameObject::getFirstGameObjectOfType(GameObject::T_PLAYER);

		Vec2 mouse_tile = screenToWorld(getMousePos() + getCamera());
		int tempx = ((int)mouse_tile.x+16) / 32;
		int tempy = ((int)mouse_tile.y+16) / 32;
		mouse_tile.setElements(tempx*32, tempy*32);


		//determine button positions

		Vec2 last_screen_pos = worldToScreen(player->command_queue.getLastPosition(player->pos)) - getCamera();
		Vec2 container_tl = last_screen_pos + Vec2(48, -64);
		Vec2 container_size(96, 128);

		if(container_tl.x < 0)
			container_tl.x = 0;
		else if(container_tl.x > SCREEN_WIDTH - container_size.x)
			container_tl.x = SCREEN_WIDTH - container_size.x;

		if(container_tl.y < 0)
			container_tl.y = 0;
		else if(container_tl.y > SCREEN_HEIGHT - container_size.y)
			container_tl.y = SCREEN_HEIGHT - container_size.y;

		float button_x = container_tl.x + container_size.x/2;
		float button_y[4];

		int i;
		for(i = 0; i < 4; i++)
		{
			button_y[i] = container_tl.y + 16 + i*32;
		}

		MoveCommandButton move_b(button_x, button_y[0], 96, 32, getTexture("move_button"));
		SlashCommandButton slash_b(button_x, button_y[1], 96, 32, getTexture("slash_button"));
		ShootCommandButton shoot_b(button_x, button_y[2], 96, 32, getTexture("shoot_button"));
		DonePlanningButton done_b(button_x, button_y[3], 96, 32, getTexture("done_button"));

		move_b.checkClicked(SDL_BUTTON_LMASK);
		slash_b.checkClicked(SDL_BUTTON_LMASK);
		shoot_b.checkClicked(SDL_BUTTON_LMASK);
		done_b.checkClicked(SDL_BUTTON_LMASK);

		drawMap();

		beginSprites();

		Habe::drawPathAll();
		Habe::drawPlannedMovementAll(player->command_queue.calculateExecutionTime());

		//right click to undo
		if(isButtonPressed(SDL_BUTTON_RMASK))
		{
			player->command_queue.popBack();
		}

		player->command_queue.render();

		GameObject::renderAll();

		endSprites();

		move_b.render();
		slash_b.render();
		shoot_b.render();
		done_b.render();
	}

	void planActionMove()
	{
		Player* player = (Player*)GameObject::getFirstGameObjectOfType(GameObject::T_PLAYER);

		Vec2 mouse_tile = screenToWorld(getMousePos() + getCamera());
		int tempx = ((int)mouse_tile.x+16) / 32;
		int tempy = ((int)mouse_tile.y+16) / 32;
		mouse_tile.setElements(tempx*32, tempy*32);

		Vec2 last_pos = player->command_queue.getLastPosition(player->pos);

		drawMap();

		beginSprites();

		Command move_command(Command::C_MOVE, last_pos, mouse_tile);

		Habe::drawPathAll();
		Habe::drawPlannedMovementAll(player->command_queue.calculateExecutionTime() + move_command.calculateExecutionTime());

		if(isButtonPressed(SDL_BUTTON_LMASK))
		{
			player->command_queue.pushCommand(move_command);
			setState(S_PLAN);
		}
		else
		{
			//draw line to mouse tile and target
			Vec2 start = worldToScreen(last_pos) - getCamera();
			Vec2 target = worldToScreen(mouse_tile) - getCamera();
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(renderer, (int)start.x,		(int)start.y,	(int)target.x,		(int)target.y);
			SDL_RenderDrawLine(renderer, (int)start.x+1,	(int)start.y,	(int)target.x+1,	(int)target.y);
			SDL_RenderDrawLine(renderer, (int)start.x,		(int)start.y+1,	(int)target.x,		(int)target.y+1);
			SDL_RenderDrawLine(renderer, (int)start.x+1,	(int)start.y+1,	(int)target.x+1,	(int)target.y+1);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			int frame_w, frame_h;
			SDL_Texture* texture = getTextureData(getTexture("target"), &frame_w, &frame_h);

			int target_ofs_x = 16, target_ofs_y = 8;

			SDL_Rect src = {
				0, 0,
				frame_w, frame_h,
			};

			SDL_Rect dst = {
				target.x - target_ofs_x, target.y - target_ofs_y,
				32, 16,
			};

			SDL_RenderCopy(renderer, texture, &src, &dst);
		}

		//right click to cancel
		if(isButtonPressed(SDL_BUTTON_RMASK))
		{
			setState(S_PLAN);
		}

		player->command_queue.render();

		GameObject::renderAll();

		endSprites();
	}

	void planActionSlash()
	{
		Player* player = (Player*)GameObject::getFirstGameObjectOfType(GameObject::T_PLAYER);

		Vec2 mouse_tile = screenToWorld(getMousePos() + getCamera());
		int tempx = ((int)mouse_tile.x+16) / 32;
		int tempy = ((int)mouse_tile.y+16) / 32;
		mouse_tile.setElements(tempx, tempy);

		Vec2 last_pos = player->command_queue.getLastPosition(player->pos);
		tempx = ((int)last_pos.x+16) / 32;
		tempy = ((int)last_pos.y+16) / 32;
		Vec2 player_tile(tempx, tempy);

		//can only slash 1 tile ahead
		if(mouse_tile.x > player_tile.x)
			mouse_tile.x = player_tile.x+1;
		else if(mouse_tile.x < player_tile.x)
			mouse_tile.x = player_tile.x-1;

		if(mouse_tile.y > player_tile.y)
			mouse_tile.y = player_tile.y+1;
		else if(mouse_tile.y < player_tile.y)
			mouse_tile.y = player_tile.y-1;

		mouse_tile *= 32;

		drawMap();

		beginSprites();

		Habe::drawPathAll();
		Habe::drawPlannedMovementAll(player->command_queue.calculateExecutionTime());

		if(isButtonPressed(SDL_BUTTON_LMASK) && !(mouse_tile == player_tile))
		{
			player->command_queue.pushCommand(Command(Command::C_SLASH, last_pos, mouse_tile));
			setState(S_PLAN);
		}
		else
		{
			//draw target
			Vec2 target = worldToScreen(mouse_tile) - getCamera();

			int frame_w, frame_h;
			SDL_Texture* texture = getTextureData(getTexture("target"), &frame_w, &frame_h);

			int target_ofs_x = 16, target_ofs_y = 8;

			SDL_Rect src = {
				0, 0,
				frame_w, frame_h,
			};

			SDL_Rect dst = {
				target.x - target_ofs_x, target.y - target_ofs_y,
				32, 16,
			};

			SDL_RenderCopy(renderer, texture, &src, &dst);
		}

		//right click to cancel
		if(isButtonPressed(SDL_BUTTON_RMASK))
		{
			setState(S_PLAN);
		}

		player->command_queue.render();

		GameObject::renderAll();

		endSprites();
	}

	void planActionShoot()
	{
		Player* player = (Player*)GameObject::getFirstGameObjectOfType(GameObject::T_PLAYER);

		Vec2 mouse_p = screenToWorld(getMousePos() + getCamera());

		Vec2 last_pos = player->command_queue.getLastPosition(player->pos);

		drawMap();

		beginSprites();

		Habe::drawPathAll();
		Habe::drawPlannedMovementAll(player->command_queue.calculateExecutionTime());

		if(isButtonPressed(SDL_BUTTON_LMASK))
		{
			player->command_queue.pushCommand(Command(Command::C_SHOOT, last_pos, mouse_p));
			setState(S_PLAN);
		}
		else
		{
			//draw line to mouse and target
			Vec2 start = worldToScreen(last_pos) - getCamera();
			Vec2 target = worldToScreen(mouse_p) - getCamera();
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(renderer, (int)start.x, (int)start.y, (int)target.x, (int)target.y);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			int frame_w, frame_h;
			SDL_Texture* texture = getTextureData(getTexture("target"), &frame_w, &frame_h);

			int target_ofs_x = 16, target_ofs_y = 8;

			SDL_Rect src = {
				0, 0,
				frame_w, frame_h,
			};

			SDL_Rect dst = {
				target.x - target_ofs_x, target.y - target_ofs_y,
				32, 16,
			};

			SDL_RenderCopy(renderer, texture, &src, &dst);
		}

		//right click to cancel
		if(isButtonPressed(SDL_BUTTON_RMASK))
		{
			setState(S_PLAN);
		}

		player->command_queue.render();

		GameObject::renderAll();

		endSprites();
	}

	void mainLoop_run()
	{
		Player* player = (Player*)GameObject::getFirstGameObjectOfType(GameObject::T_PLAYER);

		drawMap();

		beginSprites();

		player->command_queue.render();
		
		GameObject::updateAll();
		GameObject::renderAll();

		if(player->command_queue.isDone())
		{
			//check if habe count == 0 then S_LEVELCOMPLETE
			GameObject* h = GameObject::getFirstGameObjectOfType(GameObject::T_HABE);
			if(h)
			{
				setState(S_DEFEAT);
			}
			else
			{
				setState(S_LEVELCOMPLETE);
			}
			//setState(S_PLAN);
		}

		endSprites();
	}

	void waitState()
	{
		drawMap();

		beginSprites();
		
		//GameObject::updateAll();
		for(auto it = GameObject::getListBegin(); it != GameObject::getListEnd(); it++)
		{
			if((*it)->getType() == GameObject::T_PARTICLES)
				(*it)->update();
		}

		GameObject::renderAll();

		endSprites();
	}

	bool mainLoop()
	{
		switch(state)
		{
		case S_MAINMENU:
			mainMenu();
			break;

		case S_STARTLEVEL:
			startLevel();
			break;

		case S_LEVELCOMPLETE:
			levelComplete();
			break;

		case S_PLAN:
			planActionPlan();
			break;

		case S_PLANMOVE:
			planActionMove();
			break;

		case S_PLANSLASH:
			planActionSlash();
			break;

		case S_PLANSHOOT:
			planActionShoot();
			break;

		case S_RUN:
			mainLoop_run();
			break;

		case S_WAIT:
			waitState();
			break;

		case S_DEFEAT:
			defeat(getTexture("defeat"));
			break;

		case S_VICTORY:
			win();
			break;

		case S_EXIT:
			return false;
		}

		state = next_state;

		return true;
	}
}
