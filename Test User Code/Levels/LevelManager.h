#ifndef _LevelManager
#define _LevelManager

class LevelManager
{
private:
	static LevelManager* ptrInstance;

	LevelManager() = default;
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;
	~LevelManager() = default;

	static LevelManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new LevelManager();
		return *ptrInstance;
	}

	int currentLevel = 0;

	void PrivNextLevel();
	void PrivLose();

public:
	static void Initialize();
	static void NextLevel() { Instance().PrivNextLevel(); };
	static void Lose() { Instance().PrivLose(); };
	static void Terminate();
};

#endif _LevelManager