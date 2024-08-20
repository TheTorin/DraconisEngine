#ifndef _AlarmableAttorney
#define _AlarmableAttorney

#include "Alarmable.h"

class AlarmableAttorney
{
public:
	class AlarmLoop
	{
		friend class AlarmableManager;
	private:
		static void TriggerAlarm(Alarmable* alarm, AlarmableManager::ALARM_ID id) { alarm->TriggerAlarm(id); };
	};

	class Registration
	{
		friend class AlarmRegisterCmd;
		friend class AlarmDeregisterCmd;
	private:
		static void AlarmRegistration(AlarmableManager::ALARM_ID id, float time, Alarmable* alarm) { alarm->AlarmRegistration(id, time); };
		static void AlarmDeregistration(AlarmableManager::ALARM_ID id, Alarmable* alarm) { alarm->AlarmDeregistration(id); };
	};
};

#endif _AlarmableAttorney