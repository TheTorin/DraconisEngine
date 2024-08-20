#ifndef _Building
#define _Building

#include "AzulCore.h"
#include "..//DraconisEngine/GameObject.h"
#include "..//DraconisEngine/ParticleSystem.h"

class Bullet;
class Bomb;
class Building : public GameObject
{
private:
	GraphicsObject_TextureLight* pBody;
	ParticleSystem* s;
	Matrix rot;
	Matrix scale;
	Vect position;
	bool dead;

public:
	Building();
	Building(const Building&) = delete;
	Building& operator=(const Building&) = delete;
	~Building();

	void Set(Vect pos);
	void SetScale(float scale);

	void Draw() override;

	virtual void Collision(Collidable*) { DebugMsg::out("Building collided with generic collidable"); };
	virtual void Collision(Bullet*);
	virtual void Collision(Bomb*);
};

#endif _Building