#ifndef _SpriteString
#define _SpriteString

#include <vector>
#include <string>
#include "SpriteFont.h"

class SpriteString
{
public:
	using GlyphCollection = std::vector<SpriteFont::Glyph*>;

private:
	GlyphCollection glyphs;
	float height;
	float width;
	float posx;
	float posy;

public:
	SpriteString() = delete;

	///-------------------------------------------------------------------------------------------------
	/// \fn	SpriteString::SpriteString(SpriteFont* sf, std::string s, float x, float y);
	///
	/// \brief	Constructor
	///
	/// \param [in,out]	sf	If non-null, the font the string will be rendered in.
	/// \param 		   	s 	A std::string to process.
	/// \param 		   	x 	The x coordinate to begin the string at.
	/// \param 		   	y 	The y coordinate to begin the string at.
	///-------------------------------------------------------------------------------------------------

	SpriteString(SpriteFont* sf, std::string s, float x, float y);
	SpriteString(const SpriteString& other);
	SpriteString& operator=(const SpriteString&) = delete;
	~SpriteString();

	///-------------------------------------------------------------------------------------------------
	/// \fn	float SpriteString::GetHeight()
	///
	/// \brief	Gets the height of the string
	///
	/// \returns	The height.
	///-------------------------------------------------------------------------------------------------

	float GetHeight() { return height; };

	///-------------------------------------------------------------------------------------------------
	/// \fn	float SpriteString::GetWidth()
	///
	/// \brief	Gets the width of the string (width of all characters together)
	///
	/// \returns	The width.
	///-------------------------------------------------------------------------------------------------

	float GetWidth() { return width; };

	///-------------------------------------------------------------------------------------------------
	/// \fn	void SpriteString::Set(SpriteFont* sf, std::string s, float x, float y);
	///
	/// \brief	Sets the string to the given parameters
	///
	/// \param [in,out]	sf	If non-null, the font the SpriteString will use
	/// \param 		   	s 	A std::string to process.
	/// \param 		   	x 	The x coordinate to begin the string at.
	/// \param 		   	y 	The y coordinate to begin the string at.
	///-------------------------------------------------------------------------------------------------

	void Set(SpriteFont* sf, std::string s, float x, float y);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void SpriteString::Set(float x, float y);
	///
	/// \brief	Moves the string to the specified position. Does not change the font or characters.
	///
	/// \param 	x	The x coordinate to begin the string at.
	/// \param 	y	The y coordinate to begin the string at.
	///-------------------------------------------------------------------------------------------------

	void Set(float x, float y);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void SpriteString::Render();
	///
	/// \brief	Renders the string to the screen
	///-------------------------------------------------------------------------------------------------

	void Render();
};

#endif _SpriteString