#include "BotPool.h"
#include "AIBot.h"

AIBot* BotPool::getBot()
{
	AIBot* b;

	if (recycledBots.empty())
	{
		b = new AIBot();
	}
	else
	{
		b = recycledBots.top();
		recycledBots.pop();
	}

	activeBots.push_back(b);
	return b;
}

void BotPool::returnBot(AIBot* b)
{
	recycledBots.push(static_cast<AIBot*>(b));
	activeBots.remove(b);
}

int BotPool::GetBotsLeft()
{
	return activeBots.size();
}

void BotPool::Terminate()
{
	while (!activeBots.empty())
	{
		AIBot* b = activeBots.front();
		b->SubmitExit();
		activeBots.pop_front();
		recycledBots.push(b);
	}
}

BotPool::~BotPool()
{
	while (!recycledBots.empty())
	{
		delete recycledBots.top();
		recycledBots.pop();
	}
}