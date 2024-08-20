#ifndef _BotFactory
#define _BotFactory

#include "AzulCore.h"
#include "BotPool.h"

class GameObject;
class BotFactory
{
private:
	static BotFactory* ptrInstance;

	BotFactory() = default;
	BotFactory(const BotFactory&) = delete;
	BotFactory& operator=(const BotFactory&) = delete;
	~BotFactory() = default;

	static BotFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new BotFactory();
		return *ptrInstance;
	}

	BotPool pool;

	void privCreateBot(Matrix m, Vect v);
	int privGetBotsLeft();
	void privRecycleBot(GameObject* go);

public:
	static void createBot(Matrix m, Vect v) { Instance().privCreateBot(m, v); };
	static int GetBotsLeft() { return Instance().privGetBotsLeft(); };
	static void recycleBot(GameObject* go) { Instance().privRecycleBot(go); };

	static void Terminate();
};

#endif _BotFactory