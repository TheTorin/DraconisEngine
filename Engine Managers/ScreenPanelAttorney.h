#ifndef _ScreenPanelAttorney
#define _ScreenPanelAttorney

#include "ScreenPanel.h"

class ScreenPanelAttorney
{
	friend class ScreenLog;
private:
	static void Render(ScreenPanel* sp) { sp->Render(); };
};

#endif _ScreenPanelAttorney