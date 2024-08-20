#ifndef _TextureManager
#define _TextureManager

#include "AzulCore.h"
#include <map>
#include <string>
#include <stdexcept>

class TextureManager
{
	friend class TextureManagerAttorney;
private:
	static TextureManager* ptrInstance;

	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	~TextureManager() = default;

	static TextureManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TextureManager();
		return *ptrInstance;
	};

	std::map<std::string, Texture*> LoadedTextures;

	Texture* privGet(const std::string& key);
	int privLoad(const std::string key, const char* const path);
	int privLoad(const std::string key, const unsigned char& red, const unsigned char& blue, const unsigned char& green);

	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static Texture* TextureManager::Get(const std::string& key)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Gets a texture* using the given key
	///
	/// \param 	key	The key the texture is stored under.
	///
	/// \returns	Error if it fails, else a pointer to a Texture.
	///-------------------------------------------------------------------------------------------------

	static Texture* Get(const std::string& key) { return Instance().privGet(key); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int TextureManager::Load(const std::string key, const char* const path)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Loads the texture and stores it under the given key
	///
	/// \param 	key 	The key to store the texture under.
	/// \param 	path	Full pathname of the file. Default pathway starts under Assets
	///
	/// \returns	EXIT_SUCCESS on success, EXIT_FAILURE on failure
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string key, const char* const path) { return Instance().privLoad(key, path); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int TextureManager::Load(const std::string key, const unsigned char& red, const unsigned char& blue, const unsigned char& green)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Loads a 'texture' consisting of the given RGB value
	///
	/// \param 	key  	The key to store the texture under.
	/// \param 	red  	The red value. Ranges from 0 to 255
	/// \param 	blue 	The blue value. Ranges from 0  to 255
	/// \param 	green	The green value. Ranges from 0 to 255
	///
	/// \returns	EXIT_SUCCESS on success, EXIT_FAILURE on failure
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string key, const unsigned char& red, const unsigned char& blue, const unsigned char& green) { return Instance().privLoad(key, red, green, blue); };
};

#endif _TextureManager