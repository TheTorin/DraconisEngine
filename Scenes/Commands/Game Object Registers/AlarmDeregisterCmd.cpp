#include "AlarmDeregisterCmd.h"
#include "AlarmableAttorney.h"

AlarmDeregisterCmd::AlarmDeregisterCmd(Alarmable* alarm, AlarmableManager::ALARM_ID id)
	:ptrAlarm(alarm), AlarmID(id)
{

}

void AlarmDeregisterCmd::Execute()
{
	AlarmableAttorney::Registration::AlarmDeregistration(AlarmID, ptrAlarm);
}