#ifndef _BasicBox
#define _BasicBox

#include "..//DraconisEngine/GameObject.h"

class BasicBox : public GameObject
{
private:
	GraphicsObject_TextureLight* box;
	
	Matrix scale;
	Matrix rot;
	Vect pos;

public:
	BasicBox();
	BasicBox(const BasicBox&) = delete;
	BasicBox& operator=(const BasicBox&) = delete;
	~BasicBox();

	void Update() override;
	void Draw() override;
};

#endif _BasicBox