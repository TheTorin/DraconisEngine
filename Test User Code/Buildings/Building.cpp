#include "Building.h"
#include "..//DraconisEngine/Color.h"
#include "BuildingManager.h"
#include "../DraconisEngine/ParticleEffectManager.h"
#include "..//DraconisEngine/ParticleEffect.h"

Building::Building()
{
	Vect LightColor = Color::White;
	Vect LightPos(1.0f, 100.0f, 100.0f, 1.0f);
	pBody = new GraphicsObject_TextureLight(ModelManager::Get("Apartment"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Building"), LightColor, LightPos);

	rot = Matrix(ROT_X, -3.1415f / 2.0f);
	scale = Matrix(IDENTITY);
	Matrix world = rot;
	position = Vect(0, 0, 0);
	pBody->SetWorld(world);

	SetCollidableGroup<Building>();
	SetColliderModel(pBody->getModel(), VolumeType::AABB);
	UpdateCollisionData(world);
	SubmitCollisionRegistration();
	SubmitDrawRegistration();
	dead = false;
	BuildingManager::AddBuilding();

	s = new ParticleSystem();
	s->Add(ParticleEffectManager::Get("SmokeTrail"), 3.0f);
	s->Add(ParticleEffectManager::Get("SparksFast"), 0.0f);
}

void Building::Set(Vect pos)
{
	position = pos;
	Matrix world = rot * scale * Matrix(TRANS, pos);
	pBody->SetWorld(world);
	UpdateCollisionData(world);
}

void Building::SetScale(float sc)
{
	scale = Matrix(SCALE, sc, sc, sc);
	Matrix world = rot * scale * Matrix(TRANS, position);
	pBody->SetWorld(world);
	UpdateCollisionData(world);
}

void Building::Draw()
{
	pBody->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void Building::Collision(Bullet*)
{
	SubmitCollisionDeregistration();
	if (!dead) 
	{
		SubmitDrawDeregistration();
		BuildingManager::RemoveBuilding();
		s->SetAll(Matrix(IDENTITY), position);
		s->Start();
	}
	dead = true;
}

void Building::Collision(Bomb*)
{
	SubmitCollisionDeregistration();
	if (!dead) 
	{
		SubmitDrawDeregistration();
		BuildingManager::RemoveBuilding();
		s->SetAll(Matrix(IDENTITY), position);
		s->Start();
	}
	dead = true;
}

Building::~Building()
{
	delete pBody;
	delete s;
}