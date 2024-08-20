#ifndef _ScreenLog
#define _ScreenLog

#include <vector>
#include "ScreenPanel.h"

class SpriteFont;
class DraconisSprite;
class ScreenLog
{
	friend class ScreenLogAttorney;
private:
	static ScreenLog* ptrInstance;

	ScreenLog() = default;
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator=(const ScreenLog&) = delete;
	~ScreenLog() = default;

	static ScreenLog& Instance()
	{
		if (!ptrInstance) {
			ptrInstance = new ScreenLog();
			ptrInstance->Initialize();
		}
		return *ptrInstance;
	}

	float anchorX;
	float anchorY;
	static char DebugChar[256];
	SpriteFont* sf;

	using MessageCol = std::vector<std::string>;
	MessageCol messages;

	using PanelVec = std::vector<ScreenPanel*>;
	PanelVec panels;

	void privRender();
	static void Initialize();
	static void Render() { Instance().privRender(); };
	static void Terminate();

	static SpriteFont* GetSpriteFont() { return Instance().sf; };

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void ScreenLog::Add(char* m, ...);
	///
	/// \brief	Renders the string to the debug log
	///
	/// This function accepts parameters similar to printf, such as %i, %3.1f, e.t.c
	/// 
	/// \param [in,out]	m  	If non-null, a char to render.
	/// \param 		   	...	Variable arguments providing additional information.
	///-------------------------------------------------------------------------------------------------

	static void Add(char* m, ...);

	///-------------------------------------------------------------------------------------------------
	/// \fn	static ScreenPanel* ScreenLog::GetPanel(float x, float y);
	///
	/// \brief	Gets a panel. Currently not working
	///
	/// \param 	x	The x coordinate.
	/// \param 	y	The y coordinate.
	///
	/// \returns	Null if it fails, else the panel.
	///-------------------------------------------------------------------------------------------------

	static ScreenPanel* GetPanel(float x, float y);

	///-------------------------------------------------------------------------------------------------
	/// \fn	static ScreenPanel* ScreenLog::GetPanel(float x, float y, DraconisSprite* ds);
	///
	/// \brief	Gets a panel. Currently not working
	///
	/// \param 		   	x 	The x coordinate.
	/// \param 		   	y 	The y coordinate.
	/// \param [in,out]	ds	If non-null, the ds.
	///
	/// \returns	Null if it fails, else the panel.
	///-------------------------------------------------------------------------------------------------

	static ScreenPanel* GetPanel(float x, float y, DraconisSprite* ds);
};

#endif _ScreenLog