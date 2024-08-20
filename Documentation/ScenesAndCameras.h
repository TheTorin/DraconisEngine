///-------------------------------------------------------------------------------------------------
/// \file	DraconisEngine\ScenesAndCameras.h.
///
/// \brief	Information about scenes and cameras
/// 
/// ### Scenes ###
/// 
/// Scenes are not stored, and are destroyed upon changing scenes.
/// In order to change to a new scene, use the `SceneManager::setNextScene(MyScene*)` function.
/// The scene will be changed on the next frame.
/// 
/// ### Cameras ###
/// 
/// There are two types of cameras. Perspective cameras (3D) and orthographic (2D)
/// Currently, each scene starts off with its own default 3D camera, a god cam, and a default 2D camera.
/// There is currently no way to change the 2D camera, and all 2D sprites automatically render themselves to the current scene's 2D camera
/// In order to change the current camera, a new camera must be created.
/// To create a camera correctly, it must be given three pieces of information.
/// 1. The size of the viewport  
/// 2. The perspective (near/far fields, angle of view)  
/// 3. The orientation and position to place the camera at  
/// Any time a camera is moved or changed, the changes do not take effect until the `MyCamera*->updateCamera()` function is called.
/// Here is an example of creating a camera that follows the player around:
/// 
/// \code{.cpp}
/// 		   MyPlayer::MyPlayer()
/// 		   {
/// 			    ...
/// 			    CamShipOffset = Vect(0, 140, -300);
///					CamLookAt = Vect(0, 50, 100);
///					
/// 		       	followCam = new Camera(Camera::Type::PERSPECTIVE_3D);
///					followCam->setViewport(0, 0, Draconis::getWindowWidth(), Draconis::getWindowHeight());
///					followCam->setPerspective(35.0f, float(Draconis::getWindowWidth()) / float(Draconis::getWindowHeight()), 1.0f, 5000.0f);
///					//This instructs the Scene to set this as the current 3D camera
///					SceneManager::getCurrentScene()->setCurrentCamera(followCam);
///			   }
///			   
///			   void MyPlayer::Update()
///			   {
///			   		Matrix RotationPosition = RotationMatrix * Matrix(TRANS, PositionVector);	// This is the worldmat without scaling
///					Vect vNewCamPos = CamLookAt * RotationPosition;		// This moves the cam position relative to the player's position and rotation
///					Vect vNewLookAt = CamShipOffset * RotationPosition;   // This moves the look-at point relative to the player's position and rotation
///					followCam->setOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
///					followCam->updateCamera();
///			   }
///	\endcode
///
///-------------------------------------------------------------------------------------------------
