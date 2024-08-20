#ifndef _SpriteFontManager
#define _SpriteFontManager

#include <map>
#include <string>

class SpriteFont;
class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;
private:
	static SpriteFontManager* ptrInstance;

	SpriteFontManager() = default;
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator=(const SpriteFontManager&) = delete;
	~SpriteFontManager() = default;

	static SpriteFontManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new SpriteFontManager();
		return *ptrInstance;
	}

	using SpriteMap = std::map<std::string, SpriteFont*>;
	SpriteMap LoadedFonts;

	int privLoad(const std::string& key, const char* const path);
	SpriteFont* privGet(const std::string& key);

	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int SpriteFontManager::Load(const std::string& key, const char* const path)
	/// \ingroup RESOURCES
	/// \brief	Loads a font into the resources
	///
	/// \param 	key 	The key to store the font under
	/// \param 	path	Full pathname of the file for the font.
	///
	/// \returns	EXIT_SUCCESS on success, EXIT_FAILURE and error on failure
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string& key, const char* const path) { return Instance().privLoad(key, path); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static SpriteFont* SpriteFontManager::Get(const std::string& key)
	/// \ingroup RESOURCES
	/// \brief	Gets a sprite font* using the given key
	///
	/// \param 	key	The key to get.
	///
	/// \returns	Null if it fails, else a pointer to a SpriteFont.
	///-------------------------------------------------------------------------------------------------

	static SpriteFont* Get(const std::string& key) { return Instance().privGet(key); };
};

#endif _SpriteFontManager