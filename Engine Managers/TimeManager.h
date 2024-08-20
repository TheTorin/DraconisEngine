#ifndef _TimeManager
#define _TimeManager

#include "FreezeTime.h"

class TimeManager
{
	friend class TimeManagerAttorney;
private:
	static TimeManager* ptrInstance;

	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager() = default;

	static TimeManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new TimeManager();
		return *ptrInstance;
	}

	FreezeTime FrzTime;

	float currTime;
	float frameTime;
	float prevTime;

	float privGetFrameTime();
	float privGetTime();

	void ProcessTime(float sys_time);
	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static float TimeManager::getFrameTime()
	///
	/// \brief	Gets time it took to process the frame
	///
	/// \returns	The time (in seconds) since the last frame
	///-------------------------------------------------------------------------------------------------

	static float getFrameTime() { return Instance().privGetFrameTime(); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static float TimeManager::getTime()
	///
	/// \brief	Gets the total time the game has been running.
	/// \ingroup INFO
	/// 
	/// Note: This does NOT include the time spent while the game has been frozen via the FreezeTime interface.
	/// 
	/// \returns	The time (in seconds).
	///-------------------------------------------------------------------------------------------------

	static float getTime() { return Instance().privGetTime(); };
};

#endif _TimeManager