#include "PlaneBotManager.h"
#include "PlaneBotFactory.h"

PlaneBotManager::PlaneBotManager()
{
	float time = (rand() % 2) + 4.0f;
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}

void PlaneBotManager::Alarm0()
{
	float angle = (float)(rand() % 6);
	float x = (rand() % 2000) - 1000.0f;
	float z = (rand() % 2000) - 1000.0f;
	PlaneBotFactory::CreatePlane(Matrix(ROT_Y, angle), Vect(x, 50, z));
	float time = (rand() % 2) + 4.0f;
	SubmitAlarmRegistration(AlarmableManager::ALARM_0, time);
}