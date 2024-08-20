#include "SpriteFontManager.h"
#include "SpriteFont.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;

int SpriteFontManager::privLoad(const std::string& key, const char* const path)
{
	SpriteMap::iterator it = LoadedFonts.find(key);
	if (it != LoadedFonts.end()) {
		throw std::invalid_argument("Error while loading sprite font: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	SpriteFont* sf = new SpriteFont(path);
	LoadedFonts.insert({ key, sf });
	return EXIT_SUCCESS;
}

SpriteFont* SpriteFontManager::privGet(const std::string& key)
{
	SpriteMap::iterator it = LoadedFonts.find(key);
	if (it == LoadedFonts.end())
	{
		throw std::invalid_argument("Error while retrieving sprite font: Key " + key + " not found!");
		return NULL;
	}
	return it->second;
}

void SpriteFontManager::Terminate()
{
	for (SpriteMap::iterator it = Instance().LoadedFonts.begin(); it != Instance().LoadedFonts.end(); it++)
	{
		delete it->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}