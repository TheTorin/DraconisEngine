#include "ScreenPanel.h"
#include "ScreenLogAttorney.h"
#include "ImageManager.h"
#include "DraconisSprite.h"
#include "SpriteFont.h"
#include "SpriteString.h"

ScreenPanel::ScreenPanel(float x, float y)
{
	anchorX = x;
	anchorY = y;
	messageHeight = 0;
	messageWidth = 0;
	sf = ScreenLogAttorney::Panel::GetSpriteFont();
	bg = new DraconisSprite("Border");
	bg->SetCenter(0, 0);
}

ScreenPanel::ScreenPanel(float x, float y, DraconisSprite* background)
{
	anchorX = x;
	anchorY = y;
	sf = ScreenLogAttorney::Panel::GetSpriteFont();
	bg = background;
	bg->SetCenter(0, 0);
}

void ScreenPanel::Add(char* m, ...)
{
	va_list args;

	va_start(args, m);
	vsprintf_s(DebugChar, m, args);
	va_end(args);

	std::string s(DebugChar);

	SpriteString* sps = new SpriteString(sf, s, 0, 0);
	messageHeight += sps->GetHeight();
	if (messageWidth < sps->GetWidth()) messageWidth = sps->GetWidth();

	messages.push_back(s);
}

void ScreenPanel::Render()
{
	bg->SetScalePixel(messageWidth + 30, messageHeight + 30);
	bg->SetPosition(anchorX - 15, anchorY - 15);
	bg->Render();

	float tHeight = 0;
	SpriteString* s = new SpriteString(sf, "", 0, 0);

	for (size_t i = 0; i < messages.size(); i++)
	{
		s->Set(sf, messages[i], anchorX, anchorY);
		s->Render();
		tHeight -= s->GetHeight();
	}
}

ScreenPanel::~ScreenPanel()
{
	messages.clear();
	delete bg;
}