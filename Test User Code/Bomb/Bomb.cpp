#include "Bomb.h"
#include "BombFactory.h"

Bomb::Bomb()
{
	body = new GraphicsObject_ColorNoTexture(ModelManager::Get("Sphere"), ShaderManager::Get("ColorNoTex"));
	rot = Matrix(IDENTITY);
	pos = Vect(0, 0, 0);

	Matrix world = scale * rot * Matrix(TRANS, pos);
	body->SetWorld(world);

	SetCollidableGroup<Bomb>();
	SetColliderModel(body->getModel(), VolumeType::BSPHERE);
	UpdateCollisionData(world);
}

void Bomb::Initialize(Vect position)
{
	pos = position;
	scale = Matrix(IDENTITY);
	goBoom = false;
	fallSpeed = baseFallSpeed;
}

void Bomb::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration();
}

void Bomb::Update()
{
	pos += Vect(0, -fallSpeed, 0);

	Matrix world = scale * rot * Matrix(TRANS, pos);
	body->SetWorld(world);
	UpdateCollisionData(world);
}

void Bomb::Draw()
{
	body->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void Bomb::Alarm0()
{
	SubmitExit();
}

void Bomb::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);

	BombFactory::RecycleBomb(this);
}

void Bomb::Collision(Collidable*)
{
	if (!goBoom)
	{
		scale = Matrix(SCALE, Vect(15, 15, 15));
		SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
		goBoom = true;
		fallSpeed = 0;
	}
	else
	{
		SubmitCollisionDeregistration();
	}
}

void Bomb::TerrainCollision()
{
	if (!goBoom)
	{
		scale = Matrix(SCALE, Vect(15, 15, 15));
		SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
		goBoom = true;
		fallSpeed = 0;
	}
	else
	{
		SubmitCollisionDeregistration();
	}
}

Bomb::~Bomb()
{
	delete body;
}