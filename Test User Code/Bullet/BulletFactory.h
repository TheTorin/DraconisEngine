#ifndef _BulletFactory
#define _BulletFactory

#include "AzulCore.h"
#include "BulletPool.h"

class GameObject;
class BulletFactory
{
private:
	static BulletFactory* ptrInstance;

	BulletFactory() = default;
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	~BulletFactory() = default;

	static BulletFactory& Instance()
	{
		if (!ptrInstance) ptrInstance = new BulletFactory();
		return *ptrInstance;
	}

	BulletPool pool;

	void privCreateBullet(Matrix rot, Vect pos);
	void privRecycleBullet(GameObject* go);

public:
	static void createBullet(Matrix rot, Vect pos) { Instance().privCreateBullet(rot, pos); };
	static void recycleBullet(GameObject* go) { Instance().privRecycleBullet(go); };
	static void Terminate();
};

#endif _BulletFactory