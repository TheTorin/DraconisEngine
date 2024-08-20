// SpriteFont

#ifndef _SpriteFont
#define _SpriteFont

#include "DraconisSprite.h"
#include "AzulCore.h"
#include <map>
#include <string>
#include <xmllite.h>

class SpriteFont
{
public:
	using Key = int;
	using Glyph = DraconisSprite;

private:
	std::string Name;
	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);

public:
	SpriteFont() = delete;

	///-------------------------------------------------------------------------------------------------
	/// \fn	SpriteFont::SpriteFont(std::string path);
	///
	/// \brief	Constructor
	///
	/// \param 	path	Full pathname of the font to use.
	///-------------------------------------------------------------------------------------------------

	SpriteFont(std::string path);
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// \fn	Glyph* SpriteFont::GetGlyph(char c);
	///
	/// \brief	Returns the sprite in this objects font for the given character
	///
	/// \param 	c	The character.
	///
	/// \returns	Null if it fails, else the sprite of the given character.
	///-------------------------------------------------------------------------------------------------

	Glyph* GetGlyph(char c);
};

#endif _SpriteFont