#ifndef _BombFactory
#define _BombFactory

#include "BombPool.h"
#include "AzulCore.h"

class GameObject;
class BombFactory
{
private:
	static BombFactory* ptrInstance;

	BombFactory() = default;
	BombFactory(const BombFactory&) = delete;
	BombFactory& operator=(const BombFactory&) = delete;
	~BombFactory() = default;

	static BombFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new BombFactory();
		return *ptrInstance;
	}

	BombPool pool;

	void PrivCreateBomb(Vect pos);
	void PrivRecycleBomb(GameObject* go);

public:
	static void CreateBomb(Vect pos) { Instance().PrivCreateBomb(pos); };
	static void RecycleBomb(GameObject* go) { Instance().PrivRecycleBomb(go); };
	static void Terminate();
};

#endif _BombFactory