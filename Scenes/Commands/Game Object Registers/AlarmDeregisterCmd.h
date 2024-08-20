#ifndef _AlarmDeregisterCmd
#define _AlarmDeregisterCmd

#include "SceneCommandBase.h"
#include "AlarmableManager.h"

class Alarmable;
class AlarmDeregisterCmd : public SceneCommandBase
{
private:
	Alarmable* ptrAlarm;
	AlarmableManager::ALARM_ID AlarmID;

public:
	AlarmDeregisterCmd(Alarmable* alarm, AlarmableManager::ALARM_ID id);
	AlarmDeregisterCmd(const AlarmDeregisterCmd&) = delete;
	AlarmDeregisterCmd& operator=(const AlarmDeregisterCmd&) = delete;
	~AlarmDeregisterCmd() = default;

	void Execute() override;
};

#endif _AlarmDeregisterCmd