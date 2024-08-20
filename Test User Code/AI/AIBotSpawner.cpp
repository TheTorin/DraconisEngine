#include "AIBotSpawner.h"
#include "BotFactory.h"

AIBotSpawner::AIBotSpawner()
{
	float time = (rand() % 2) + 2.0f;
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}

void AIBotSpawner::Alarm0()
{
	float angle = (float)(rand() % 6);
	float x = (rand() % 2000) - 1000.0f;
	float z = (rand() % 2000) - 1000.0f;
	BotFactory::createBot(Matrix(ROT_Y, angle), Vect(x, 50, z));
	
	float time = (rand() % 2) + 4.0f;
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}