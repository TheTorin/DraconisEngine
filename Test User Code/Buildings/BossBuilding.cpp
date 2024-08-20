#include "BossBuilding.h"
#include "BossManager.h"
#include "..//DraconisEngine/Color.h"

BossBuilding::BossBuilding()
{
	Vect lightCol = Color::LightGray;
	Vect lightPos = Vect(0, 500, 0);
	pBody = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("Cube"), ShaderManager::Get("ColorNoTexLight"), lightCol, lightPos);
	rot = Matrix(IDENTITY);
	scale = Matrix(SCALE, Vect(200, 200, 200));
	pos = Vect(0, 70, 0);

	Matrix world = rot * scale * Matrix(TRANS, pos);
	pBody->SetWorld(world);

	SetCollidableGroup<BossBuilding>();
	SetColliderModel(pBody->getModel(), VolumeType::OBB);
	UpdateCollisionData(world);
	SubmitDrawRegistration();
	SubmitCollisionRegistration();

	BossManager::Register(this);
	health = 15;
}

void BossBuilding::Draw()
{
	rot *= Matrix(ROT_Y, 0.01f);
	Matrix world = rot * scale * Matrix(TRANS, pos);
	pBody->SetWorld(world);
	UpdateCollisionData(world);

	pBody->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

BossBuilding::~BossBuilding()
{
	delete pBody;
}