#ifndef _ScreenPanel
#define _ScreenPanel

#include <vector>

class DraconisSprite;
class SpriteFont;
class ScreenPanel
{
	friend class ScreenPanelAttorney;
private:
	SpriteFont* sf;
	DraconisSprite* bg;
	float anchorX;
	float anchorY;
	float messageHeight;
	float messageWidth;
	char DebugChar[256];

	std::vector<std::string> messages;

	void Render();

public:
	ScreenPanel() = delete;

	///-------------------------------------------------------------------------------------------------
	/// \fn	ScreenPanel::ScreenPanel(float x, float y);
	///
	/// \brief	Constructor for Screen Panel
	///
	/// \param 	x	The x coordinate.
	/// \param 	y	The y coordinate.
	///-------------------------------------------------------------------------------------------------

	ScreenPanel(float x, float y);
	ScreenPanel(float x, float y, DraconisSprite* background);
	ScreenPanel(const ScreenPanel&) = delete;
	ScreenPanel& operator=(const ScreenPanel&) = delete;
	~ScreenPanel();

	void Add(char* m, ...);
};

#endif _ScreenPanel