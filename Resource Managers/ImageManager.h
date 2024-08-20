#ifndef _ImageManager
#define _ImageManager

#include "AzulCore.h"
#include <map>
#include <string>

class ImageManager
{
	friend class ImageManagerAttorney;
private:
	static ImageManager* ptrInstance;

	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	~ImageManager() = default;

	static ImageManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new ImageManager();
		return *ptrInstance;
	}

	std::map<std::string, Image*> LoadedImages;

	Image* privGet(const std::string& key);
	int privLoad(const std::string& key, Texture* tex);
	int privLoad(const std::string& key, Texture* tex, Rect* r);
	
	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static Image* ImageManager::Get(const std::string& key)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Gets a stored image* using the given key
	///
	/// \param 	key	The key the image is stored under.
	///
	/// \returns	Error if it fails, else a pointer to an Image.
	///-------------------------------------------------------------------------------------------------

	static Image* Get(const std::string& key) { return Instance().privGet(key); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int ImageManager::Load(const std::string& key, Texture* tex)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Loads the entire texture into an image
	///
	/// \param 		   	key	The key to store the image under.
	/// \param [in,out]	tex	If non-null, the texture.
	///
	/// \returns	EXIT_SUCCESS or EXIT_FAILURE
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string& key, Texture* tex) { return Instance().privLoad(key, tex); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int ImageManager::Load(const std::string& key, Texture* tex, Rect* r)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Loads a portion of the texture into an image
	///
	/// \param 		   	key	The key to store the image under.
	/// \param [in,out]	tex	If non-null, the texture.
	/// \param [in,out]	r  	If non-null, a Rect defining the area of the texture to use.
	///
	/// \returns	EXIT_SUCCESS or EXIT_FAILURE
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string& key, Texture* tex, Rect* r) { return Instance().privLoad(key, tex, r); };
};

#endif _ImageManager