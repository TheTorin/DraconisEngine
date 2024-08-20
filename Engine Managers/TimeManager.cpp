#include "TimeManager.h"
#include "DraconisAttorney.h"

TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager::TimeManager()
{
	currTime = 0;
	prevTime = 0;
	frameTime = 0;
}

void TimeManager::ProcessTime(float sys_time)
{
	prevTime = currTime;

	//currTime = sys_time;
	currTime = FrzTime.GetTimeInSeconds(sys_time);

	frameTime = currTime - prevTime;
}

float TimeManager::privGetFrameTime()
{
	return frameTime;
}

float TimeManager::privGetTime()
{
	return currTime;
}

void TimeManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}