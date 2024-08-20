#ifndef _DraconisAttorney
#define _DraconisAttorney

#include "Draconis.h"

class DraconisAttorney
{
public:
	class TimeControl
	{
		friend class TimeManager;
		friend class FreezeTime;
	private:
		static float getEngineTime() { return Draconis::Instance().getTime(); };
	};
};

#endif _DraconisAttorney