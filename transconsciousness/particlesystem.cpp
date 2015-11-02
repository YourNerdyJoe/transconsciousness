#include "particlesystem.h"
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>


Particle::Particle()
{
}

Particle::Particle(float world_x, float world_y, int anchor_x, int anchor_y, float w, float h, int tex_id) : 
Sprite(world_x, world_y, anchor_x, anchor_y, w, h, tex_id)
{
}

Particle::~Particle()
{
}

void Particle::draw()
{
	SDL_Rect dst = {
		(int)v[0].x - getCamera().x,
		(int)v[0].y - getCamera().y,
		(int)w,
		(int)h,
	};

	//try{
	SDL_SetRenderDrawColor(renderer, r,g,b,a);
	SDL_RenderDrawRect(renderer, &dst);
	SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	//}catch(std::exception& e){
	//	printf("exception\n");
	//}
}

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::ParticleSystem(float x, float y, float w, float h, float spr_w, float spr_h, int max_particles, int life_time, float dir1, float dir2, float spd, unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
GameObject(x,y,0,0,w,h,spr_w,spr_h,-1,false,false), max_particles(max_particles), life_time(life_time), particles(nullptr), r(r), g(g), b(b), a(a)
{
	particles = new Particle[max_particles];
	if(!particles) printf("particle alloc error\n");
	int i;
	for(i = 0; i < max_particles; i++)
	{
		particles[i] = Particle(x, y, 0, 0, spr_w, spr_h, -1);
		particles[i].setColor(r, g, b, a);
		
		float dir = dir1 + (float)(rand() % ((int)((dir2 - dir1)*100)))/100;
		float speed = ((float)(rand() % (int)(spd * 100))/100)+0.1f;

		dir *= M_PI/180;

		particles[i].vel.setElements(cos(dir)*speed, sin(dir)*speed);

		particles[i].life_time = (rand() % life_time) + 1;
	}
}

ParticleSystem::~ParticleSystem()
{
	if(particles) delete[] particles;
}

void ParticleSystem::update()
{
	if(life_time <= 0)
	{
		markTrash();
	}

	int i;
	for(i = 0; i < max_particles; i++)
	{
		if(particles[i].life_time > 0)
		{
			particles[i].world_pos += particles[i].vel;

			particles[i].spriteCalculateVertices();
			//pushSprite(particles[i]);
			particles[i].draw();

			particles[i].life_time--;
		}
	}
	life_time--;
}
