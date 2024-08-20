#ifndef _Alarmable
#define _Alarmable

#include "RegistrationStates.h"
#include "AlarmableManager.h"

class AlarmRegisterCmd;
class AlarmDeregisterCmd;
class Alarmable
{
	friend class AlarmableAttorney;
private:
	struct RegistrationData {
		RegistrationStates regState;
		AlarmRegisterCmd* pRegister;
		AlarmDeregisterCmd* pDeregister;
		AlarmableManager::ListRef pDeleteRef;
	};

	RegistrationData regData[AlarmableManager::NUM_ALARMS];

	void TriggerAlarm(AlarmableManager::ALARM_ID id);

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Alarmable::Alarm0()
	/// \ingroup ENGINE_CALLED_EVENTS
	/// 
	/// \brief	The function to execute when Alarm0 is triggered
	///
	/// \note There are currently 3 available alarms
	///-------------------------------------------------------------------------------------------------

	virtual void Alarm0() {};
	virtual void Alarm1() {};
	virtual void Alarm2() {};

	void AlarmDeregistration(AlarmableManager::ALARM_ID id);
	void AlarmRegistration(AlarmableManager::ALARM_ID id, float time);

public:
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator=(const Alarmable&) = delete;
	virtual ~Alarmable();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float time);
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submit alarm registration for given alarm
	///
	/// \param 	id  	The enum identifier for which alarm to set (via AlarmableManager::ALARM_ID).
	/// \param 	time	The time, in seconds, to call the alarm in.
	///-------------------------------------------------------------------------------------------------

	void SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float time);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);
	/// \ingroup (DE)REGISTRATION_EVENTS
	/// 
	/// \brief	Submit alarm deregistration for given alarm
	///
	/// \param 	id	The enum identifier for which alarm to deregister (via AlarmableManager::ALARM_ID).
	///-------------------------------------------------------------------------------------------------

	void SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);
};

#endif _Alarmable