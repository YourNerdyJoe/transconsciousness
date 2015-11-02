#ifndef _LEVEL_H_
#define _LEVEL_H_

typedef void (*level_function)();

class Level
{
	level_function p_alloc;
	//level_function p_init;
	//level_function p_update;
	//level_function p_dealloc;

public:
	Level();
	Level(level_function p_alloc);//, level_function p_init, level_function p_update, level_function p_dealloc);

	inline void alloc()		{ if(p_alloc)	p_alloc();	}
	//inline void init()		{ if(p_init)	p_init();	}
	//inline void update()	{ if(p_update)	p_update();	}
	//inline void dealloc()	{ if(p_dealloc) p_dealloc();}
};

#define GEN_LEVEL_FUNC(x)	\
	void alloc_level##x();	
	//void init_level##x();	
	//void update_level##x();	
	//void dealloc_level##x()

#define LEVEL_FUNC(x)	\
	alloc_level##x//, init_level##x, update_level##x, dealloc_level##x

#endif
