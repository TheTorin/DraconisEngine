#ifndef _GodCamManager
#define _GodCamManager

#include "GameObject.h"

class Camera;
class GodCamManager : public GameObject
{
private:
	Camera* godCam;

	const Vect upCam = Vect(0.0f, 1.0f, 0.0f);
	Vect rightCam;
	Vect posCam;
	Vect lookAtCam;
	float angle;

	const Matrix rightRot = Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, upCam, 0.05f);
	const Matrix leftRot = Matrix(RotAxisAngleType::ROT_AXIS_ANGLE, upCam, -0.05f);

	Matrix upRot;
	Matrix downRot;

public:
	GodCamManager(Camera* cam);
	GodCamManager(const GodCamManager&) = delete;
	GodCamManager& operator=(const GodCamManager&) = delete;
	~GodCamManager();

	void KeyHeldDown(AZUL_KEY k) override;
};

#endif _GodCamManager