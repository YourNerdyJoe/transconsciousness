#include "commandqueue.h"
#include "player.h"
#include "damagemessage.h"
#include "isometric.h"
#include <math.h>
#include "particlesystem.h"
#include "slashanimation.h"

#define PLAYER_MAX_SPEED 5

//frames required to execute command
const int command_time_execute[] = {
	0,	//C_MOVE
	15,	//C_SLASH
	25,	//C_SHOOT
};

bool CommandQueue::executeMove(Command& cur, Player& player)
{
	Vec2 offset = cur.target - player.pos;

	player.getSprite().animation = radianToSpriteDirection(offset.getDirection());

	float distance_remaining = offset.getMagnitude();
	if(distance_remaining <= PLAYER_MAX_SPEED)
	{
		player.pos = cur.target;
		return true;
	}

	offset = offset.getNormalized() * PLAYER_MAX_SPEED;
	player.pos += offset;

	return false;
}

#define SLASH_DISTANCE 32

bool CommandQueue::executeSlash(Command& cur, Player& player)
{
	//Vec2 dir_vec = cur.target - player.pos;
	//float target_dir = dir_vec.getDirection();
	//float dir_min = target_

	//get tile pos
	int px, py;
	px = (int)player.pos.x + 16;
	py = (int)player.pos.y + 16;
	px /= 32; //px*= 32;
	py /= 32; //py*= 32;

	int tx, ty;
	tx = (int)cur.target.x + 16;
	ty = (int)cur.target.y + 16;
	tx /= 32; //tx*= 32;
	ty /= 32; //ty*= 32;

	int affected_tiles[3][2];

	affected_tiles[1][0] = tx;
	affected_tiles[1][1] = ty;

	if(px == tx)
	{
		affected_tiles[0][0] = tx - 1;
		affected_tiles[0][1] = ty;
		affected_tiles[2][0] = tx + 1;
		affected_tiles[2][1] = ty;
	}
	else if(py == ty)
	{
		affected_tiles[0][0] = tx;
		affected_tiles[0][1] = ty - 1;
		affected_tiles[2][0] = tx;
		affected_tiles[2][1] = ty + 1;
	}
	else
	{
		affected_tiles[0][0] = px;
		affected_tiles[0][1] = ty;
		affected_tiles[2][0] = tx;
		affected_tiles[2][1] = py;
	}

	//deal damage first
	if(cur.time_elapsed == 0)
	{
		for(auto it = GameObject::getListBegin(); it != GameObject::getListEnd(); it++)
		{
			if((GameObject*)&player != (*it))
			{
				int ox, oy;
				ox = (int)(*it)->pos.x + 16;
				oy = (int)(*it)->pos.y + 16;
				ox /= 32;
				oy /= 32;

				int i;
				for(i = 0; i < 3; i++)
				{
					if(ox == affected_tiles[i][0] && oy == affected_tiles[i][1])
					{
						(*it)->handleMessage(&DamageMessage((GameObject*)&player, 3));
					}
				}
			}
		}

		//draw slash animation
		Vec2 offset = cur.target - player.pos;
		float dir = worldToScreen(offset).getDirection();
		SlashAnimation* slash_anim = new SlashAnimation(player.pos.x  + tx - px, player.pos.y + ty - py, dir * 180/M_PI);

		player.getSprite().animation = radianToSpriteDirection(offset.getDirection());

		playSound("slash");
	}

	int i;
	for(i = 0; i < 3; i++)
	{
		Vec2 r_pos(affected_tiles[i][0] * 32.0f, affected_tiles[i][1] * 32.0f);
		r_pos = worldToScreen(r_pos);
		SDL_Rect r = {
			(int)(r_pos.x-16 - getCamera().x),
			(int)(r_pos.y-8 - getCamera().y),
			32,
			16,
		};
		SDL_SetRenderDrawColor(renderer, 255,0,0,255);
		SDL_RenderDrawRect(renderer, &r);
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	}

	if(cur.time_elapsed >= command_time_execute[Command::C_SLASH]-1)
		return true;
	else
		return false;
}

struct HitableData
{
	GameObject* obj;
	float distance;
	HitableData(GameObject* obj, float dist) : obj(obj), distance(dist) {}
};

bool CommandQueue::executeShoot(Command& cur, Player& player)
{
	if(cur.time_elapsed == 0)
	{
		std::list<HitableData> hitable_list;

		Vec2 ray = (cur.target - cur.start).getNormalized();
		Vec2 normal(ray.y, -ray.x);

		for(auto it = GameObject::getListBegin(); it != GameObject::getListEnd(); it++)
		{
			GameObject* obj = *it;
			if(obj->is_solid || obj->getType() == GameObject::T_HABE)
			{
				float dist = ray.dot(obj->pos - cur.start);
				if(dist > 0)
					hitable_list.push_back(HitableData(obj, dist));
			}
		}

		hitable_list.sort([](HitableData& first, HitableData& second) {
			return first.distance < second.distance;
		});

		for(auto it = hitable_list.begin(); it != hitable_list.end(); it++)
		{
			GameObject* obj = it->obj;
			float proj = normal.dot(obj->pos - cur.start);

			//use w as radius of circle (close enough)
			if(abs(proj) < obj->w)
			{
				obj->handleMessage(&DamageMessage(&player, 1));

				break;
			}
		}

		player.getSprite().animation = radianToSpriteDirection(ray.getDirection());

		//create particle effect
		float part_dir = ray.getDirection() * 180/M_PI;
		//if(part_dir < 0.0f) part_dir += 360.0f;

		ParticleSystem* part_sys = new ParticleSystem(player.pos.x, player.pos.y, 2, 2, 2, 2, 180, 50, part_dir-1, part_dir+1, 35, 0x0, 0x80, 0xFF, 0xFF);
		if(!part_sys) printf("particle error\n");

		playSound("shoot");
	}
	return (cur.time_elapsed >= command_time_execute[Command::C_SHOOT]-1);
}

void CommandQueue::execute(Player& player)
{
	if(isDone()) return;

	Command& cur = queue.front();
	bool done = false;

	switch(cur.type)
	{
	case Command::C_MOVE:
		done = executeMove(cur, player);
		break;

	case Command::C_SLASH:
		done = executeSlash(cur, player);
		break;

	case Command::C_SHOOT:
		done = executeShoot(cur, player);
		break;
	}

	cur.time_elapsed++;
	
	if(done)
		queue.pop_front();
}

void CommandQueue::render()
{
	if(isDone()) return;

	Vec2 target_offset(16, 8);

	//draw movement lines

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for(auto it = queue.begin(); it != queue.end(); it++)
	{
		Command& c = *it;
		Vec2 start = worldToScreen(c.start) - getCamera();
		Vec2 target = worldToScreen(c.target) - getCamera();
		
		//draw thick line for move and thin for shoot
		switch(c.type)
		{
		case Command::C_MOVE:
			SDL_RenderDrawLine(renderer, (int)start.x+1,	(int)start.y,	(int)target.x+1,	(int)target.y);
			SDL_RenderDrawLine(renderer, (int)start.x,		(int)start.y+1,	(int)target.x,		(int)target.y+1);
			SDL_RenderDrawLine(renderer, (int)start.x+1,	(int)start.y+1,	(int)target.x+1,	(int)target.y+1);
		case Command::C_SHOOT:
			SDL_RenderDrawLine(renderer, (int)start.x,		(int)start.y,	(int)target.x,		(int)target.y);
		}
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


	//draw targets

	int frame_w, frame_h;
	SDL_Texture* texture = getTextureData(getTexture("target"), &frame_w, &frame_h);

	SDL_Rect src = {
		0, 0,
		frame_w, frame_h,
	};

	SDL_Rect dst = {
		0, 0,
		32, 16,
	};

	auto it = queue.begin();
	Vec2 target = worldToScreen(it->start) - target_offset - getCamera();
	dst.x = (int)target.x;
	dst.y = (int)target.y;
	SDL_RenderCopy(renderer, texture, &src, &dst);

	for(; it != queue.end(); it++)
	{
		Vec2 target = worldToScreen(it->target) - target_offset - getCamera();
		src.x = 0;
		src.y = 0;
		src.w = frame_w;
		src.h = frame_h;
		dst.x = (int)target.x;
		dst.y = (int)target.y;
		dst.w = 32;
		dst.h = 16;
		SDL_RenderCopy(renderer, texture, &src, &dst);
	}
}

Vec2 CommandQueue::getLastPosition(Vec2& v)
{
	for(auto it = queue.rbegin(); it != queue.rend(); it++)
	{
		if(it->type == Command::C_MOVE)
			return it->target;
	}
	return v;
}

int Command::calculateExecutionTime()
{
	if(type == C_MOVE)
	{
		float distance = (target - start).getMagnitude();
		int mod = (int)distance % PLAYER_MAX_SPEED;
		return (int)distance / PLAYER_MAX_SPEED + ((mod) ? 1 : 0);
	}
	else
	{
		return command_time_execute[type];
	}
}

int CommandQueue::calculateExecutionTime()
{
	int time = 0;
	for(auto it = queue.begin(); it != queue.end(); it++)
	{
		time += it->calculateExecutionTime();
	}

	return time;
}
