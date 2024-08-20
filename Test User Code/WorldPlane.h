#ifndef _WorldPlane
#define _WorldPlane

#include "../DraconisEngine/GameObject.h"
#include "AzulCore.h"

class WorldPlane : public GameObject
{
private:
	GraphicsObject_TextureFlat* pGObj_Plane;
	GraphicsObject_ColorNoTexture* pGObj_Axis;
	Model* plane;

public:
	WorldPlane();
	WorldPlane(const WorldPlane&) = delete;
	WorldPlane& operator = (const WorldPlane&) = delete;
	~WorldPlane();

	void Draw() override;
	void KeyPressed(AZUL_KEY k) override;
};

#endif _WorldPlane