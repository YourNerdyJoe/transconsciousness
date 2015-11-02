#ifndef _COMMAND_QUEUE_H_
#define _COMMAND_QUEUE_H_
#include "vec2.h"
#include <list>

struct Command
{
	enum Type {
		C_MOVE = 0,
		C_SLASH,
		C_SHOOT,
	};

	Type type;
	Vec2 start;
	Vec2 target;
	int time_elapsed;

	Command(Type type, Vec2& start, Vec2& target) : type(type), start(start), target(target), time_elapsed(0) {}

	int calculateExecutionTime();
};

//frames required to execute command
extern const int command_time_execute[];

class Player;

class CommandQueue
{
	std::list<Command> queue;

	bool executeMove(Command& cur, Player& player);
	bool executeSlash(Command& cur, Player& player);
	bool executeShoot(Command& cur, Player& player);
public:
	inline void pushCommand(const Command& c) { queue.push_back(c); }
	inline void popBack() { queue.pop_back(); }
	inline bool isDone() { return queue.empty(); }

	void execute(Player& player);
	void render();

	Vec2 getLastPosition(Vec2& v);

	int calculateExecutionTime();
};

#endif
