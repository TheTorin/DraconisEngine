#ifndef _ScreenLogManager
#define _ScreenLogManager

#include "ScreenLog.h"

class ScreenLogAttorney
{
public:
	class Engine
	{
		friend class Draconis;
	private:
		static void Render() { ScreenLog::Render(); };
		static void Terminate() { ScreenLog::Terminate(); };
	};
	class Panel
	{
		friend class ScreenPanel;
	private:
		static SpriteFont* GetSpriteFont() { return ScreenLog::GetSpriteFont(); };
	};
};

#endif _ScreenLogManager