#ifndef _PlayerManager
#define _PlayerManager

#include "AzulCore.h"

class Player;
class PlayerManager
{
private:
	static PlayerManager* ptrInstance;

	PlayerManager() = default;
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;
	~PlayerManager() = default;

	static PlayerManager& Instance()
	{
		if (!ptrInstance) ptrInstance = new PlayerManager();
		return *ptrInstance;
	}

	Player* currPlayer;
	Vect spawnPosition;

	void privInit();
	int privGetPlayerHP();
	Player* privGetPlayer() { return currPlayer; };
	Vect privGetPlayerPos();
	Matrix privGetPlayerRot();

public:
	static void Initialize() { Instance().privInit(); };
	static void SetSpawnPosition(Vect pos) { Instance().spawnPosition = pos; };
	static int getPlayerHP() { return Instance().privGetPlayerHP(); };
	static Player* getPlayer() { return Instance().privGetPlayer(); };
	static Vect getPlayerPos() { return Instance().privGetPlayerPos(); };
	static Matrix getPlayerRot() { return Instance().privGetPlayerRot(); };

	static void Terminate();
};

#endif _PlayerManager