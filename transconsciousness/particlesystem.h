#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_
#include "gameobject.h"

class Particle : public Sprite
{
public:
	Vec2 vel;
	unsigned char r, g, b, a;
	int life_time;

	Particle();
	Particle(float world_x, float world_y, int anchor_x, int anchor_y, float w, float h, int tex_id);
	~Particle();

	inline void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	virtual void draw();
};

class ParticleSystem : public GameObject
{
	int max_particles;
	int life_time;
	Particle* particles;
public:
	unsigned char r, g, b, a;

	ParticleSystem();
	ParticleSystem(float x, float y, float w, float h, float spr_w, float spr_h, int max_particles, int life_time, float dir1, float dir2, float spd, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	~ParticleSystem();

	Type getType() { return T_PARTICLES; }

	void update();
};

#endif
