#ifndef _BotPool
#define _BotPool

#include <stack>
#include <list>

class AIBot;
class BotPool
{
private:
	std::list<AIBot*> activeBots;
	std::stack<AIBot*> recycledBots;

public:
	BotPool() = default;
	BotPool(const BotPool&) = delete;
	BotPool& operator=(const BotPool&) = delete;
	~BotPool();

	AIBot* getBot();
	int GetBotsLeft();
	void returnBot(AIBot* b);

	void Terminate();
};

#endif _BotPool