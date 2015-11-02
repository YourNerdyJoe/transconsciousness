#include "leveldata.h"
#include "player.h"
#include "civilian.h"
#include "habecrawler.h"
#include "damagemessage.h"

void alloc_level1()
{
	Player* player = new Player(288, 288);

	Civilian* c1 = new Civilian(288, 32, LEFT_DOWN);
	HabeCrawler* h1 = new HabeCrawler(224, 32, c1);

	h1->handleMessage(&DamageMessage(nullptr, 2));
}

void alloc_level2()
{
	Player* player = new Player(288, 288);

	Civilian* c1 = new Civilian(320, 128, LEFT_DOWN);
	HabeCrawler* h1 = new HabeCrawler(224, 128, c1);
}

void alloc_level3()
{
	Player* player = new Player(288, 288);

	Civilian* c1 = new Civilian(32, 32, 0);
	Civilian* c2 = new Civilian(448, 448, 0);

	HabeCrawler* h1 = new HabeCrawler(192, 32, c1);
	HabeCrawler* h2 = new HabeCrawler(32, 192, c1);

	HabeCrawler* h3 = new HabeCrawler(256, 448, c2);
	HabeCrawler* h4 = new HabeCrawler(448, 192, c2);

	DamageMessage d(nullptr, 2);	//set hp to 1
	h3->handleMessage(&d);
	h4->handleMessage(&d);
}

void alloc_level4()
{
	Player* player = new Player(256, 256);
	Civilian* civ = new Civilian(288, 32, LEFT_DOWN);
	HabeCrawler* h1 = new HabeCrawler(28, 32, (GameObject*)civ);
	civ = new Civilian(224, 416, RIGHT_DOWN);
	HabeCrawler* h2 = new HabeCrawler(48, 288, civ);
	HabeCrawler* h3 = new HabeCrawler(288, 416, civ);
	h3->handleMessage(&DamageMessage(nullptr, 2));
}

void alloc_level5()
{
	Player* player = new Player(256, 256);

	Civilian* c1 = new Civilian(96, 96, RIGHT_DOWN);
	Civilian* c2 = new Civilian(128, 96, RIGHT_DOWN);
	Civilian* c3 = new Civilian(160, 96, RIGHT_DOWN);

	HabeCrawler* h1 = new HabeCrawler(96, 320, c1);
	HabeCrawler* h2 = new HabeCrawler(128, 320, c2);
	HabeCrawler* h3 = new HabeCrawler(160, 320, c3);
}

void alloc_level6()
{
	Player* player = new Player(256, 256);

	Civilian* c1 = new Civilian(160, 32, RIGHT_DOWN);
	Civilian* c2 = new Civilian(32, 320, RIGHT_DOWN);
	Civilian* c3 = new Civilian(448, 448, RIGHT_DOWN);

	HabeCrawler* h1 = new HabeCrawler(64, 32, c1);
	HabeCrawler* h2 = new HabeCrawler(320, 32, c1);

	HabeCrawler* h3 = new HabeCrawler(32, 96, c2);
	HabeCrawler* h4 = new HabeCrawler(96, 320, c2);

	HabeCrawler* h5 = new HabeCrawler(448, 192, c3);
	HabeCrawler* h6 = new HabeCrawler(160, 448, c3);

	DamageMessage d(nullptr, 2);

	h1->handleMessage(&d);
	h2->handleMessage(&d);
	h3->handleMessage(&d);
	h4->handleMessage(&d);
	h5->handleMessage(&d);
	h6->handleMessage(&d);
}

/*
void init_level1()
{
}

void update_level1()
{
}

void dealloc_level1()
{
}
*/
