#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>

class Alarmable;
class AlarmableManager
{
public:
	enum ALARM_ID { ALARM_0, ALARM_1, ALARM_2 };

private:
	using AlarmEvent = std::pair<Alarmable*, ALARM_ID>;
	using TimelineMap = std::multimap<float, AlarmEvent>;
	using AlarmPair = std::pair<float, AlarmEvent>;
	TimelineMap timeline;
	float totalTime;

public:
	AlarmableManager();
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;
	~AlarmableManager() = default;

	static const int NUM_ALARMS = 3;

	using ListRef = TimelineMap::iterator;

	void ProcessAlarms();

	void Register(float time, Alarmable* alarm, ALARM_ID id, ListRef& ref);
	void Deregister(ListRef ref);
};

#endif _AlarmableManager