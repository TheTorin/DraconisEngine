#include "ShaderManager.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;

ShaderObject* ShaderManager::privGet(const std::string& key)
{
	std::map<std::string, ShaderObject*>::iterator it = LoadedShaders.find(key);
	if (it == LoadedShaders.end()) {
		throw std::invalid_argument("Error, no shader found with the given key of " + key);
		return NULL;
	}
	return it->second;
}

int ShaderManager::privLoad(const std::string key, const char* const path)
{
	std::map<std::string, ShaderObject*>::iterator it = LoadedShaders.find(key);
	if (it != LoadedShaders.end()) {
		throw std::invalid_argument("Error while loading shader: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	ShaderObject* m = new ShaderObject(path);
	LoadedShaders.insert({ key, m });
	return EXIT_SUCCESS;
}

void ShaderManager::Terminate()
{
	for (std::map<std::string, ShaderObject*>::iterator it = Instance().LoadedShaders.begin(); it != Instance().LoadedShaders.end(); it++) {
		delete it->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}