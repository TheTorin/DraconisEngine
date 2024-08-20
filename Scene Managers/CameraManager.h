#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"

class GodCamManager;
class CameraManager
{
private:
	Camera* defaultCam;
	Camera* default2DCam;
	Camera* godCam;

	Camera* currentCam;

	GodCamManager* godManager;

public:
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	~CameraManager();

	///-------------------------------------------------------------------------------------------------
	/// \fn	Camera* CameraManager::getCurrentCamera();
	///
	/// \brief	Gets current 3D camera
	///
	/// \returns	Null if it fails, else the current camera.
	///-------------------------------------------------------------------------------------------------

	Camera* getCurrentCamera();

	///-------------------------------------------------------------------------------------------------
	/// \fn	Camera* CameraManager::get2DCamera();
	///
	/// \brief	Gets current 2D camera
	///
	/// \returns	Null if it fails, else the 2D camera.
	///-------------------------------------------------------------------------------------------------

	Camera* get2DCamera();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void CameraManager::setCurrentCamera(Camera* newcam);
	///
	/// \brief	Changes current camera to given one
	///
	/// \param [in,out]	newcam	If non-null, the newcam.
	///-------------------------------------------------------------------------------------------------

	void setCurrentCamera(Camera* newcam);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void CameraManager::setGodCamAsCurrent();
	///
	/// \brief	Sets the god camera as the current camera
	///-------------------------------------------------------------------------------------------------

	void setGodCamAsCurrent();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void CameraManager::setDefaultAsCurrent();
	///
	/// \brief	Sets default, starting camera as the current one
	///-------------------------------------------------------------------------------------------------

	void setDefaultAsCurrent();
};

#endif _CameraManager