#include "TextureManager.h"

TextureManager* TextureManager::ptrInstance = nullptr;

Texture* TextureManager::privGet(const std::string& key)
{
	std::map<std::string, Texture*>::iterator it = LoadedTextures.find(key);
	if (it == LoadedTextures.end()) {
		throw std::invalid_argument("Error, no texture found with the given key of " + key);
		return NULL;
	}
	return it->second;
}

int TextureManager::privLoad(const std::string key, const char* const path)
{
	std::map<std::string, Texture*>::iterator it = LoadedTextures.find(key);
	if (it != LoadedTextures.end()) {
		throw std::invalid_argument("Error while loading texture: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	Texture* m = new Texture(path);
	LoadedTextures.insert({ key, m });
	return EXIT_SUCCESS;
}

int TextureManager::privLoad(const std::string key, const unsigned char& red, const unsigned char& blue, const unsigned char& green)
{
	std::map<std::string, Texture*>::iterator it = LoadedTextures.find(key);
	if (it != LoadedTextures.end()) {
		throw std::invalid_argument("Error while loading texture: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	Texture* m = new Texture(red, green, blue);
	LoadedTextures.insert({ key, m });
	return EXIT_SUCCESS;
}

void TextureManager::Terminate()
{
	for (std::map<std::string, Texture*>::iterator it = Instance().LoadedTextures.begin(); it != Instance().LoadedTextures.end(); it++) {
		delete it->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}