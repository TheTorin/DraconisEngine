#ifndef _BossBuilding
#define _BossBuilding

#include "AzulCore.h"
#include "..//DraconisEngine/GameObject.h"

class Bullet;
class BossBuilding : public GameObject
{
private:
	GraphicsObject_ColorNoTextureLight* pBody;
	Matrix rot;
	Matrix scale;
	Vect pos;
	int health;

public:
	BossBuilding();
	BossBuilding(const BossBuilding&) = delete;
	BossBuilding& operator=(const BossBuilding&) = delete;
	~BossBuilding();

	int GetHealth() { return health; };

	void Draw() override;

	virtual void Collision(Collidable*) { DebugMsg::out("Building collided with generic collidable"); };
	virtual void Collision(Bullet*) { --health; };
};

#endif _BossBuilding