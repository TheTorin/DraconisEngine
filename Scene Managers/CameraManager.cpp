#include "CameraManager.h"
#include "GodCamManager.h"
#include "Draconis.h"

CameraManager::CameraManager()
{
	//3D Camera
	defaultCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	defaultCam->setViewport(0, 0, Draconis::getWindowWidth(), Draconis::getWindowHeight());
	defaultCam->setPerspective(35.0f, float(Draconis::getWindowWidth()) / float(Draconis::getWindowHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(150.0f, 150.0f, 300.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	defaultCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	defaultCam->updateCamera();  // Note: if the camera moves/changes, we need to call update again

	//2D Camera
	default2DCam = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	default2DCam->setViewport(0, 0, Draconis::getWindowWidth(), Draconis::getWindowHeight());
	default2DCam->setOrthographic(-0.5f * Draconis::getWindowWidth(), 0.5f * Draconis::getWindowWidth(),
								-0.5f * Draconis::getWindowHeight(), 0.5f * Draconis::getWindowHeight(),
								1.0f, 1000.0f);

	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	default2DCam->setOrientAndPosition(up3DCam, lookAt2DCam, pos2DCam);
	default2DCam->updateCamera();

	//God Camera
	godCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	godCam->setViewport(0, 0, Draconis::getWindowWidth(), Draconis::getWindowHeight());
	godCam->setPerspective(35.0f, float(Draconis::getWindowWidth()) / float(Draconis::getWindowHeight()), 1.0f, 5000.0f);
	godCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);

	godManager = NULL;

	currentCam = defaultCam;
}

Camera* CameraManager::getCurrentCamera()
{
	return currentCam;
}

Camera* CameraManager::get2DCamera()
{
	return default2DCam;
}

void CameraManager::setCurrentCamera(Camera* newcam)
{
	currentCam = newcam;
}

void CameraManager::setDefaultAsCurrent()
{
	currentCam = defaultCam;
}

void CameraManager::setGodCamAsCurrent()
{
	if (godManager == NULL) godManager = new GodCamManager(godCam);

	currentCam = godCam;
}

CameraManager::~CameraManager()
{
	delete default2DCam;
	delete defaultCam;
	delete godManager;
	delete godCam;
}