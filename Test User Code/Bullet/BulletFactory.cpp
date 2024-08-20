#include "BulletFactory.h"
#include "Bullet.h"

BulletFactory* BulletFactory::ptrInstance = nullptr;

void BulletFactory::privCreateBullet(Matrix rot, Vect pos)
{
	Bullet* b = pool.getBullet();

	b->Initialize(rot, pos);
	b->SubmitEntry();
}

void BulletFactory::privRecycleBullet(GameObject* go)
{
	pool.returnBullet(static_cast<Bullet*>(go));
}

void BulletFactory::Terminate()
{
	Instance().pool.Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}