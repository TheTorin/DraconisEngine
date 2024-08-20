#include "BotManager.h"
#include "BotFactory.h"
#include "AzulCore.h"

BotManager* BotManager::ptrInstance = nullptr;

void BotManager::privInit()
{
	for (int i = 0; i < initBots; i++)
	{
		float x = (rand() % 2000) - 1500.0f;
		float z = (rand() & 3000) - 1500.0f;

		Vect pos = Vect(x, 0.0f, z);
		BotFactory::createBot(Matrix(IDENTITY), pos);
	}
}

int BotManager::privGetBotsLeft()
{
	return BotFactory::GetBotsLeft();
}

void BotManager::Terminate()
{
	BotFactory::Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}