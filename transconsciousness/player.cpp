#include "player.h"
#include "sys.h"
#include "animation.h"

Player::Player() : GameObject(0, 0, 31, 48, 32, 32, 64, 64, getTexture("habe_flier"), false, false)
{
	addComponent(new Animation(this, 4, 5));
}

Player::Player(float x, float y) : GameObject(x, y, 31, 48, 32, 32, 64, 64, getTexture("habe_flier"), false, false)
{
	addComponent(new Animation(this, 4, 5));
}

Player::~Player()
{
	//printf("bye\n");
}

#define PLAYER_SPEED 5

void Player::update()
{
	/*if(isKeyDown(SDL_SCANCODE_W))
	{
		pos.y -= PLAYER_SPEED;
	}
	if(isKeyDown(SDL_SCANCODE_S))
	{
		pos.y += PLAYER_SPEED;
	}
	if(isKeyDown(SDL_SCANCODE_A))
	{
		pos.x -= PLAYER_SPEED;
	}
	if(isKeyDown(SDL_SCANCODE_D))
	{
		pos.x += PLAYER_SPEED;
	}*/

	command_queue.execute(*this);
}

void Player::objectHandleMessage(const Message* msg)
{
}
