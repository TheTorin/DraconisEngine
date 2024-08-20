#ifndef _BotSpawner
#define _BotSpawner

class Player;
class BotManager
{
private:
	static BotManager* ptrInstance;

	BotManager() = default;
	BotManager(const BotManager&) = delete;
	BotManager& operator=(const BotManager&) = delete;
	~BotManager() = default;
	
	static BotManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new BotManager();
		return *ptrInstance;
	}
	
	int initBots = 5;

	void privInit();
	int privGetBotsLeft();

public:
	static void SetInitialBots(int bots) { Instance().initBots = bots; };
	static void Initialize() { Instance().privInit(); };
	static int GetBotsLeft() { return Instance().privGetBotsLeft(); };
	static void Terminate();
};

#endif _BotSpawner