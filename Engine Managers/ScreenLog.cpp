#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "Draconis.h"
#include "ScreenPanelAttorney.h"


ScreenLog* ScreenLog::ptrInstance = nullptr;
char ScreenLog::DebugChar[256] = {};

void ScreenLog::Initialize()
{
	Instance().anchorX = 10;
	Instance().anchorY = (float)Draconis::getWindowHeight();
	Instance().sf = SpriteFontManager::Get("Centaur");
}

void ScreenLog::Add(char* m, ...)
{
	va_list args;

	va_start(args, m);
	vsprintf_s(DebugChar, m, args);
	va_end(args);

	std::string s(DebugChar);
	Instance().messages.push_back(s);
}

void ScreenLog::privRender()
{
	float tHeight = 0;
	SpriteString* string = new SpriteString(sf, "", anchorX, anchorY);

	for (size_t i = 0; i < messages.size(); i++)
	{
		string->Set(sf, messages[i], anchorX, anchorY + tHeight);
		string->Render();
		tHeight -= string->GetHeight();
	}

	for (size_t i = 0; i < panels.size(); i++)
	{
		ScreenPanelAttorney::Render(panels[i]);
	}

	messages.clear();
	panels.clear();

	delete string;
}

ScreenPanel* ScreenLog::GetPanel(float x, float y)
{
	ScreenPanel* sp = new ScreenPanel(x, y);
	Instance().panels.push_back(sp);
	return sp;
}

ScreenPanel* ScreenLog::GetPanel(float x, float y, DraconisSprite* ds)
{
	ScreenPanel* sp = new ScreenPanel(x, y, ds);
	Instance().panels.push_back(sp);
	return sp;
}

void ScreenLog::Terminate()
{
	Instance().messages.clear();
	delete ptrInstance;
	ptrInstance = nullptr;
}