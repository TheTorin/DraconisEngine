#include "AlarmRegisterCmd.h"
#include "AlarmableAttorney.h"

AlarmRegisterCmd::AlarmRegisterCmd(Alarmable* alarm, AlarmableManager::ALARM_ID id)
	:ptrAlarm(alarm), time(0), AlarmID(id)
{

}

void AlarmRegisterCmd::Execute()
{
	AlarmableAttorney::Registration::AlarmRegistration(AlarmID, time, ptrAlarm);
}