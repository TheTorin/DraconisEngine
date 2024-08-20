#ifndef _AIBotSpawner
#define _AIBotSpawner

#include "..//DraconisEngine/GameObject.h"

class AIBotSpawner : public GameObject
{
private:

public:
	AIBotSpawner();
	AIBotSpawner(const AIBotSpawner&) = delete;
	AIBotSpawner& operator=(const AIBotSpawner&) = delete;
	~AIBotSpawner() = default;

	void Alarm0() override;
};

#endif _AIBotSpawner