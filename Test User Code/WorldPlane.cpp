#include "WorldPlane.h"
#include "TestScene.h"

WorldPlane::WorldPlane()
{
	Vect LightColor(0.50f, 1.50f, 0.50f, 1.5f);
	Vect LightPos(1.0f, 10.0f, 1.0f, 1.0f);
	//pGObj_Plane = new GraphicsObject_ColorNoTextureLight(ModelManager::Get("Plane"), ShaderManager::Get("ColorNoTexLight"), LightColor, LightPos);

	plane = new Model(100, 100, 100);

	pGObj_Plane = new GraphicsObject_TextureFlat(plane, ShaderManager::Get("ObjTex"), TextureManager::Get("Grass"));
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::Get("Axis"), ShaderManager::Get("ColorNoTex"));

	Matrix world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);
	world = Matrix(SCALE, 400, 400, 400);
	pGObj_Plane->SetWorld(world);

	Drawable::SubmitDrawRegistration();
	SubmitInputRegistration(AZUL_KEY::KEY_EQUAL, EventType::KEY_PRESSED);
}

void WorldPlane::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_EQUAL)
	{
		SceneManager::setNextScene(new TestScene());
	}
}

void WorldPlane::Draw()
{
	pGObj_Plane->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	pGObj_Axis->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

WorldPlane::~WorldPlane()
{
	delete plane;
	delete pGObj_Axis;
	delete pGObj_Plane;
}