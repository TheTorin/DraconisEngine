#include "Bullet.h"
#include "BulletFactory.h"
#include "..//DraconisEngine/TimeManager.h"

Bullet::Bullet()
{
	Vect LightColor(0.0f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	bulletBody = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("Sphere"), ShaderManager::Get("ColorNoTexLight"), LightColor, LightPos);

	bulletScale.set(SCALE, 1.0f, 1.0f, 1.0f);
	bulletRot.set(IDENTITY);
	bulletPos.set(0, 0, 0);

	SetCollidableGroup<Bullet>();
	SetColliderModel(bulletBody->getModel(), VolumeType::BSPHERE);
}

void Bullet::Initialize(Matrix rot, Vect pos)
{
	bulletRot = rot;
	bulletPos = pos;
	grav = 0;
}

void Bullet::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration();
}

void Bullet::Collision(Player*)
{
	SubmitExit();
}

void Bullet::Collision(AIBot*)
{
	SubmitExit();
}

void Bullet::Collision(BossBuilding*)
{
	SubmitExit();
}

void Bullet::Update()
{
	bulletPos += Vect(0, grav, 1) * bulletRot * speed * TimeManager::getFrameTime();
	grav -= 0.001f;

	Matrix world = bulletScale * bulletRot * Matrix(TRANS, bulletPos);
	bulletBody->SetWorld(world);
	UpdateCollisionData(world);
}

void Bullet::Draw()
{
	bulletBody->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void Bullet::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();

	BulletFactory::recycleBullet(this);
}

Bullet::~Bullet()
{
	delete bulletBody;
}