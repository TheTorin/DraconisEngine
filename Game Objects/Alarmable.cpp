#include "Alarmable.h"
#include "AlarmRegisterCmd.h"
#include "AlarmDeregisterCmd.h"
#include "SceneManager.h"
#include "SceneBaseAttorney.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < AlarmableManager::NUM_ALARMS; i++)
	{
		regData[i].regState = RegistrationStates::CURRENTLY_DEREGISTERED;
		AlarmableManager::ALARM_ID id = static_cast<AlarmableManager::ALARM_ID>(i);
		regData[i].pRegister = new AlarmRegisterCmd(this, id);
		regData[i].pDeregister = new AlarmDeregisterCmd(this, id);
	}
}

void Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float time)
{
	assert(regData[id].regState == RegistrationStates::CURRENTLY_DEREGISTERED);
	regData[id].pRegister->ChangeTime(time);
	SceneBaseAttorney::AlarmRegistration::SubmitCommand(SceneManager::getCurrentScene(), regData[id].pRegister);
	regData[id].regState = RegistrationStates::PENDING_REGISTRATION;
}

void Alarmable::AlarmRegistration(AlarmableManager::ALARM_ID id, float time)
{
	assert(regData[id].regState == RegistrationStates::PENDING_REGISTRATION);
	SceneBaseAttorney::AlarmRegistration::Register(SceneManager::getCurrentScene(), time, this, id, regData[id].pDeleteRef);
	regData[id].regState = RegistrationStates::CURRENTLY_REGISTERED;
}

void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	if (regData[id].regState != RegistrationStates::CURRENTLY_REGISTERED) return;
	SceneBaseAttorney::AlarmRegistration::SubmitCommand(SceneManager::getCurrentScene(), regData[id].pDeregister);
	regData[id].regState = RegistrationStates::PENDING_DEREGISTRATION;
}

void Alarmable::AlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(regData[id].regState == RegistrationStates::PENDING_DEREGISTRATION);
	SceneBaseAttorney::AlarmRegistration::Deregister(SceneManager::getCurrentScene(), regData[id].pDeleteRef);
	regData[id].regState = RegistrationStates::CURRENTLY_DEREGISTERED;
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	regData[id].regState = RegistrationStates::CURRENTLY_DEREGISTERED;

	switch (id)
	{
	case AlarmableManager::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		this->Alarm2();
		break;
	default:
		assert(false);
	}
}

Alarmable::~Alarmable()
{
	for (int i = 0; i < AlarmableManager::NUM_ALARMS; i++)
	{
		delete regData[i].pRegister;
		delete regData[i].pDeregister;
	}
}