#ifndef _Bomb
#define _Bomb

#include "..//DraconisEngine/GameObject.h"

class Bomb : public GameObject
{
private:
	GraphicsObject_ColorNoTexture* body;
	Matrix scale;
	Matrix rot;
	Vect pos;

	const float baseFallSpeed = 3.0f;
	float fallSpeed;
	bool goBoom;
public:
	Bomb();
	Bomb(const Bomb&) = delete;
	Bomb& operator=(const Bomb&) = delete;
	~Bomb();

	void Initialize(Vect pos);

	void Update() override;
	void Draw() override;

	void SceneEntry() override;
	void SceneExit() override;

	void Alarm0() override;

	virtual void Collision(Collidable*);
	virtual void TerrainCollision();
};

#endif _Bomb