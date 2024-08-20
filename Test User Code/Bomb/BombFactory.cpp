#include "BombFactory.h"
#include "Bomb.h"

BombFactory* BombFactory::ptrInstance = nullptr;

void BombFactory::PrivCreateBomb(Vect pos)
{
	Bomb* b = pool.getBomb();

	b->Initialize(pos);
	b->SubmitEntry();
}

void BombFactory::PrivRecycleBomb(GameObject* go)
{
	pool.returnBomb(static_cast<Bomb*>(go));
}

void BombFactory::Terminate()
{
	Instance().pool.Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}