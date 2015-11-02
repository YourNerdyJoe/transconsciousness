#ifndef _HABE_CRAWLER_H_
#define _HABE_CRAWLER_H_
#include "habe.h"

class HabeCrawler : public Habe
{
public:
	GameObject* target;

	HabeCrawler();
	HabeCrawler(float x, float y, GameObject* target);
	~HabeCrawler();

	void update();
	Vec2 plotMovement(int time);
	void drawPath();
	//void handleMessage(const Message* msg);
};

#endif
