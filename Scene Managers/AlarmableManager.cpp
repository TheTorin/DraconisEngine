#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include "TimeManager.h"

AlarmableManager::AlarmableManager()
	:totalTime(0)
{

}

void AlarmableManager::Register(float time, Alarmable* alarm, ALARM_ID id, ListRef& ref)
{
	totalTime = TimeManager::getTime();

	time += totalTime;
	
	ref = timeline.insert(AlarmPair(time, AlarmEvent(alarm, id)));
}

void AlarmableManager::Deregister(ListRef ref)
{
	timeline.erase(ref);
}

void AlarmableManager::ProcessAlarms()
{
	totalTime = TimeManager::getTime();

	for (ListRef r = timeline.begin(); r != timeline.end() && (*r).first < totalTime;)
	{
		AlarmableAttorney::AlarmLoop::TriggerAlarm((*r).second.first, (*r).second.second);
		ListRef toRemove = r;
		r++;
		timeline.erase(toRemove);
	}
}