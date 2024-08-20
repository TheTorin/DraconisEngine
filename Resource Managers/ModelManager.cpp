#include "ModelManager.h"

ModelManager* ModelManager::ptrInstance = nullptr;

Model* ModelManager::privGet(const std::string& key)
{
	std::map<std::string, Model*>::iterator it = LoadedModels.find(key);
	if (it == LoadedModels.end()) {
		throw std::invalid_argument("Error, no model found with the given key of " + key);
		return NULL;
	}
	return it->second;
}

int ModelManager::privLoad(const std::string& key, const Model::PreMadeModels model)
{
	std::map<std::string, Model*>::iterator it = LoadedModels.find(key);
	if (it != LoadedModels.end()) {
		throw std::invalid_argument("Error while loading model: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	Model* m = new Model(model);
	LoadedModels.insert({ key, m });
	return EXIT_SUCCESS;
}

int ModelManager::privLoad(const std::string key, const char* const path)
{
	std::map<std::string, Model*>::iterator it = LoadedModels.find(key);
	if (it != LoadedModels.end()) {
		throw std::invalid_argument("Error while loading model: Key " + key + " is already used!");
		return EXIT_FAILURE;
	}
	Model* m = new Model(path);
	LoadedModels.insert({ key, m });
	return EXIT_SUCCESS;
}

void ModelManager::Terminate()
{
	for (std::map<std::string, Model*>::iterator it = Instance().LoadedModels.begin(); it != Instance().LoadedModels.end(); it++) {
		delete it->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}