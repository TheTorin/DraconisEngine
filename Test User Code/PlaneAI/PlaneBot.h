#ifndef _PlaneBot
#define _PlaneBot

#include "..//DraconisEngine/GameObject.h"

class Bullet;
class PlaneBot : public GameObject
{
private:
	GraphicsObject_TextureFlat* botPlane;
	Matrix planeRot;
	Matrix planeScale;
	Vect planePos;

	Vect pivot;
	float angle;
	float angleMax;
	float speed;
	float pivotDist;
	const float halfPi = (3.14159265f / 2.0f);
	bool isTurning;

public:
	PlaneBot();
	PlaneBot(const PlaneBot&) = delete;
	PlaneBot& operator=(const PlaneBot&) = delete;
	~PlaneBot();

	void Initialize(Matrix rot, Vect pos);

	void Update() override;
	void Draw() override;

	void SceneEntry() override;
	void SceneExit() override;

	void Alarm0() override;
	void Alarm1() override;

	virtual void Collision(Collidable*) { DebugMsg::out("Bot-Plane collision with generic Collidable\n"); };
	virtual void Collision(Bullet* other);
};

#endif _PlaneBot