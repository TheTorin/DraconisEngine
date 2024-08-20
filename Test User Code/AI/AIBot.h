#ifndef _AIBot
#define _AIBot

#include "../DraconisEngine/GameObject.h"

class Building;
class Bullet;
class AIBot : public GameObject
{
private:
	GraphicsObject_TextureLight* botBody;
	GraphicsObject_TextureLight* botTurret;
	GraphicsObject_TextureLight* botBarrel;
	Matrix bodyScale;
	Matrix bodyRot;
	Matrix turretRot;
	Matrix barrelRot;
	Vect worldPos;
	Vect bodyPos;
	Vect sideVect;

	const float searchRange = 200.0f;
	const float speed = 2.0f;
	const float maxTurnSpeed = 0.2f;
	float sideMult;
	float moveMult;

	float prevX;
	float prevZ;

	bool submitMove;
	bool toMove;
	bool moveSide;
	bool nearPlayer;

	float GetAngle(float distToPlayer);

public:
	AIBot();
	AIBot(const AIBot&) = delete;
	AIBot& operator=(const AIBot&) = delete;
	~AIBot();

	void Initialize(Matrix rot, Vect pos);

	void Update() override;
	void Draw() override;

	void SceneEntry() override;
	void SceneExit() override;

	void Alarm0() override;
	void Alarm1() override;
	void Alarm2() override;

	virtual void Collision(Collidable*) { DebugMsg::out("Bot-Tank collision with generic Collidable\n"); };
	virtual void Collision(Bullet*);
	virtual void Collision(Building*);
};

#endif _AIBot