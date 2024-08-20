#ifndef _Frigate
#define _Frigate

#include "../DraconisEngine/GameObject.h"
#include "..//DraconisEngine/Terrain.h"
#include "AzulCore.h"

class Bomb;
class Bullet;
class Player : public GameObject
{
private:
	GraphicsObject_TextureLight* pGObjTankBody;
	GraphicsObject_TextureLight* pGObjTankTurret;
	GraphicsObject_TextureLight* pGObjTankBarrel;
	GraphicsObject_WireframeConstantColor* pGObjSphere;

	Vect worldPos;

	int currFrame;
public:
	Player();
	Player(const Player&) = delete;
	Player& operator =(const Player&) = delete;
	~Player();

	void Update() override;
	void Draw() override;

	void KeyPressed(AZUL_KEY k) override;
	void KeyHeldDown(AZUL_KEY k) override;

	void SetPos(Vect pos);

	Camera* followCam;

	Matrix TankScale;
	Vect TankPos;
	Matrix TankBodyRot;
	Matrix TankTurretRot;
	Matrix TankBarrelRot;
	const float ShipTransSpeed = 500;
	const float ShipRotAng = .05f;
	const float TurretRotAng = .01f;
	const float MaxBarrelHeight = -0.5f;
	float CurrBarrelHeight;
	bool BsphereToggle;

	int hp;

	float currentCooldown;
	const float maxCooldown = 1.0f;

	// Camera vars
	Vect CamShipOffset;
	Vect CamLookAt;

	Vect getWorldPos();

	virtual void Collision(Collidable*) { DebugMsg::out("Collision with generic Collidable\n"); };
	virtual void Collision(Bullet*);
	virtual void Collision(Bomb*);
	virtual void TerrainCollision() { DebugMsg::out("Collided with Terrain!\n"); };
};

#endif _Frigate