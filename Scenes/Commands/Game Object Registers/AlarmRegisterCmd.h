#ifndef _AlarmRegisterCmd
#define _AlarmRegisterCmd

#include "SceneCommandBase.h"
#include "AlarmableManager.h"

class Alarmable;
class AlarmRegisterCmd : public SceneCommandBase
{
private:
	Alarmable* ptrAlarm;
	AlarmableManager::ALARM_ID AlarmID;
	float time;

public:
	AlarmRegisterCmd(Alarmable* alarm, AlarmableManager::ALARM_ID id);
	AlarmRegisterCmd(const AlarmRegisterCmd&) = delete;
	AlarmRegisterCmd& operator=(const AlarmRegisterCmd&) = delete;
	~AlarmRegisterCmd() = default;

	void Execute() override;
	void ChangeTime(float t) { time = t; };
};

#endif _AlarmRegisterCmd