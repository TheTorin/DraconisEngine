#ifndef _ShaderManager
#define _ShaderManager

#include "AzulCore.h"
#include <map>
#include <string>
#include <stdexcept>

class ShaderManager
{
	friend class ShaderManagerAttorney;
private:
	static ShaderManager* ptrInstance;

	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	~ShaderManager() = default;

	static ShaderManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ShaderManager();
		return *ptrInstance;
	};
	
	std::map<std::string, ShaderObject*> LoadedShaders;

	ShaderObject* privGet(const std::string& key);
	int privLoad(const std::string key, const char* const path);

	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static ShaderObject* ShaderManager::Get(const std::string& key)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Gets a shader object* using the given key
	///
	/// \param 	key	The key the shader is stored under.
	///
	/// \returns	Error if it fails, else a pointer to a ShaderObject.
	///-------------------------------------------------------------------------------------------------

	static ShaderObject* Get(const std::string& key) { return Instance().privGet(key); };

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int ShaderManager::Load(const std::string key, const char* const path)
	/// \ingroup RESOURCES
	/// 
	/// \brief	Loads the shader and stores it under the given key
	///
	/// \param 	key 	The key to store the shader with.
	/// \param 	path	Full pathname of the file. The default path is the Assets folder
	///
	/// \returns	EXIT_SUCCESS on success, EXIT_FAILURE on failure
	///-------------------------------------------------------------------------------------------------

	static int Load(const std::string key, const char* const path) { return Instance().privLoad(key, path); };
};

#endif _ShaderManager