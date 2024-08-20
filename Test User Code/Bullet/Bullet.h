#ifndef _Bullet
#define _Bullet

#include "../DraconisEngine/GameObject.h"

class AIBot;
class Player;
class BossBuilding;
class Bullet : public GameObject
{
private:
	GraphicsObject_ColorNoTextureLight* bulletBody;
	Matrix bulletScale;
	Vect bulletPos;
	Matrix bulletRot;
	const float speed = 250.0f;
	float grav;

public:
	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	~Bullet();

	void Initialize(Matrix rot, Vect pos);

	void SceneEntry() override;
	void SceneExit() override;

	void Update() override;
	void Draw() override;

	virtual void Collision(Collidable*) { DebugMsg::out("Collision with generic Collidable\n"); };
	virtual void Collision(AIBot*);
	virtual void Collision(Player*);
	virtual void Collision(BossBuilding*);
	virtual void TerrainCollision() { SubmitExit(); };
};

#endif _Bullet