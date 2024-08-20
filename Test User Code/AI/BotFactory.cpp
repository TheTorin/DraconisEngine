#include "BotFactory.h"
#include "AIBot.h"

BotFactory* BotFactory::ptrInstance = nullptr;

void BotFactory::privCreateBot(Matrix m, Vect v)
{
	AIBot* b = pool.getBot();

	b->Initialize(m, v);
	b->SubmitEntry();
}

void BotFactory::privRecycleBot(GameObject* go)
{
	pool.returnBot(static_cast<AIBot*>(go));
}

int BotFactory::privGetBotsLeft()
{
	return pool.GetBotsLeft();
}

void BotFactory::Terminate()
{
	Instance().pool.Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}