#ifndef _ModelManager
#define _ModelManager

#include "AzulCore.h"
#include <map>
#include <string>
#include <stdexcept>

class ModelManager
{
	friend class ModelManagerAttorney;
private:
	static ModelManager* ptrInstance;

	ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	~ModelManager() = default;

	static ModelManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ModelManager();
		return *ptrInstance;
	};
	
	std::map<std::string, Model*> LoadedModels;

	Model* privGet(const std::string& key);
	int privLoad(const std::string& key, const Model::PreMadeModels model);
	int privLoad(const std::string key, const char* const path);

	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static Model* ModelManager::Get(const std::string& key)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Gets a model* using the given key
	///
	/// \param 	key	The key the Model is stored under.
	///
	/// \returns	Error if it fails, else a pointer to a Model.
	///-------------------------------------------------------------------------------------------------

	static Model* Get(const std::string& key) { return Instance().privGet(key); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int ModelManager::Load(const std::string& key, const Model::PreMadeModels model)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Loads one of the PreMadeModels
	///
	/// \param 	key  	The key that the model will be stored under.
	/// \param 	model	The model to use. Stored under Model::PreMadeModels::
	///
	/// \returns	EXIT_SUCCESS on success, EXIT_FAILURE on failure
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string& key, const Model::PreMadeModels model) { return Instance().privLoad(key, model); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int ModelManager::Load(const std::string key, const char* const path)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Loads the model at the given path.
	///
	/// \param 	key 	The key that the model will be stored under.
	/// \param 	path	Full pathname of the file. The default path is the Assets folder.
	///
	/// \returns	EXIT_SUCCESS on success, EXIT_FAILURE on failure
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string key, const char* const path) { return Instance().privLoad(key, path); };
};

#endif _ModelManager