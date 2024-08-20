#include "BasicBox.h"

BasicBox::BasicBox()
{
	Vect LightColor(0.50f, 0.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 10.0f, 1.0f, 1.0f);

	box = new GraphicsObject_TextureLight(ModelManager::Get("Cube"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Green"), LightColor, LightPos);

	rot.set(IDENTITY);
	scale.set(SCALE, 20.0f, 20.0f, 20.0f);
	pos.set(0.0f, 0.0f, 0.0f);

	Matrix world = scale * rot * Matrix(TRANS, pos);
	box->SetWorld(world);

	SubmitUpdateRegistration();
	SubmitDrawRegistration();
}

void BasicBox::Update()
{
	rot *= Matrix(ROT_Y, 0.01f);
	Matrix world = scale * rot * Matrix(TRANS, pos);
	box->SetWorld(world);
}

void BasicBox::Draw()
{
	box->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

BasicBox::~BasicBox()
{
	delete box;
}