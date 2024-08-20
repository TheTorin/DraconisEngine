#ifndef _TimeManagerAttorney
#define _TimeManageAttorney

#include "TimeManager.h"

class TimeManagerAttorney
{
public:
	class EngineControl
	{
		friend class Draconis;
	private:
		static void ProcessTime(float sys_time) { TimeManager::Instance().ProcessTime(sys_time); };
		static void Terminate() { TimeManager::Terminate(); };
	};
};

#endif _TimeManagerAttorney