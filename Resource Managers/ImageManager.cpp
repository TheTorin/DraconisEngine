#include "ImageManager.h"
#include <stdexcept>

ImageManager* ImageManager::ptrInstance = nullptr;

Image* ImageManager::privGet(const std::string& key)
{
	std::map<std::string, Image*>::iterator it = LoadedImages.find(key);
	if (it == LoadedImages.end())
	{
		throw std::invalid_argument("Error, no Image stored with the value of " + key);
		return NULL;
	}
	return it->second;
}

int ImageManager::privLoad(const std::string& key, Texture* tex)
{
	std::map<std::string, Image*>::iterator it = LoadedImages.find(key);
	if (it != LoadedImages.end())
	{
		throw std::invalid_argument("Error while loading Image. Key " + key + " is already in use!");
		return EXIT_FAILURE;
	}
	
	Rect* r = new Rect(0.0f, 0.0f, (float)tex->getWidth(), (float)tex->getHeight());
	Image* i = new Image(tex, r);
	LoadedImages.insert({ key, i });
	return EXIT_SUCCESS;
}

int ImageManager::privLoad(const std::string& key, Texture* tex, Rect* r)
{
	std::map<std::string, Image*>::iterator it = LoadedImages.find(key);
	if (it != LoadedImages.end())
	{
		throw std::invalid_argument("Error while loading Image. Key " + key + " is already in use!");
		return EXIT_FAILURE;
	}

	Image* i = new Image(tex, r);
	LoadedImages.insert({ key, i });
	return EXIT_SUCCESS;
}

void ImageManager::Terminate()
{
	for (std::map<std::string, Image*>::iterator it = Instance().LoadedImages.begin(); it != Instance().LoadedImages.end(); it++)
	{
		delete it->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}