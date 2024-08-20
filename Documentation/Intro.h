///-------------------------------------------------------------------------------------------------
/// \file	DraconisEngine\Intro.h.
///
/// \brief	An introduction to creating your first scene
///
/// ### Creating the Scene ###
/// 
/// In order to create the first scene, a scene file must be created first. Make sure to `#include "..//DraconisEngine/SceneBase"`, and have your first scene class inherit from `public Scene`
/// Once that is done, your class will have access to the functionality of a scene. Currently, there are only two functions that need your attention.
/// 1. `void Initialize()`  
/// 2. `void SceneEnd()`  
/// These functions are called when the Scene is first loaded up and before it is destroyed respectively. Make sure to override them.
/// IMPORTANT: If `void Update()` or `void Draw()` have to be overriden for additional functionality, the base function MUST be called!
/// 
/// By now, your new scene should look somthing like this:
/// \code{.h}
/// 		 class MyScene : public Scene
/// 		 {
/// 		 public:
/// 		     void Initialize() override;
/// 		     void SceneEnd() override;
/// 		 };
/// \endcode 
/// In order to tell the engine to run this code, we can set it as the starting scene through LoadAllResources.cpp via `SceneManager::setStartScene(new MyScene());`
/// 
/// ### Populating the Scene ###
/// 
/// # Creating the Object #
/// 
/// Of course, if we were to run our code now, we would be greeted with a blank scene. So let's create an object to populate the scene with.
/// This will be a gameObject, so we will need to `#include "..//DraconisEngine/GameObject"` and inherit from `public GameObject`
/// The GameObject class has a large number of functions, but we will start off simple with `void Update()` and `void Draw()`
/// Before we begin linking the GameObject to the scene, we first need to give it a model, a shader, and possibly a light. For now, let's make it lit to demonstrate its functionality
/// Since we are using a model, a shader, and a light, we need to give the GameObject a `GraphicsObject_TextureLight*` variable to hold the graphics object
/// Now we need to initialize it. Within the constructor of the game object, we now need to communicate with the ModelManager, the ShaderManager, and the TextureManager to get their respective components
/// These files are automatically included within the GameObject header, so there is no need to reinclude them
/// We will also need to declare a light color and a light position. Here is just one example.
/// 
/// \code{.cpp}
/// 		   #include "..//DraconisEngine/Color.h"
/// 		   
/// 		   MyObject::MyObject()
/// 		   {
/// 		       Vect lightColor = Color::Blue;
/// 		       Vect lightPos = (1.0f, 10.0f, 1.0f, 1.0f);
/// 		       
/// 		       //assign info to pointer
/// 		       myGObjPointer = new GraphicsObject_TextureLight(ModelManager::Get("Cube"), ShaderManager::Get("ObjTexLight"), TextureManager::Get("Blue"), lightColor, lightPos);
/// 		   }
/// \endcode
/// 
/// Currently, this code uses a model, shader, and texture that have been loaded by default with the engine. You can view what each manager automatically loads on their documentation pages.
/// We will also go over how to add your own resources later on this page.
/// The `lightColor`, however, uses the Color namespace within the engine. This is NOT included with the base GameObject class, and must be manually included.
/// 
/// Now that we have created a graphics object, we need to tell the object where it is in relation to everything else.
/// This means providing a scale, a rotation, and a position to the object, composing its world matrix.
/// The default way of doing this is to store two matrices (scale and rotation) and one vector (position), and combining them to create the world matrix on the fly. That looks like this:
/// 
/// 
/// \code{.cpp}
/// 		   MyObject::MyObject()
/// 		   {
/// 		       scaleMatrix.set(SCALE, 10.0f, 10.0f, 10.0f);
/// 		       rotationMatrix.set(IDENTITY);
/// 		       positionVector.set(0.0f, 0.0f, 0.0f);
/// 		       
/// 		       Matrix worldMatrix = scaleMatrix * rotationMatrix * Matrix(TRANS, positionVector);
/// 		       myGObjPointer->SetWorld(worldMatrix);
/// 		   }
/// \endcode
/// 
/// Every time the world matrix is changed, either from the object moving, scaling, or rotating, the world matrix must be updated and the `SetWorld` function must be called
/// We now have an object set up within the world! Congratulations! Now we just need to link it up to the scene and make sure it gets called by the engine.
/// In order to have the engine call the objects `Update()` and `Draw()` methods, we must use the `SubmitUpdateRegistration()` and `SubmitDrawRegistration()` commands first.
/// This function sends a request to the engine to have its functions called every frame, and they will be included in the loops on the following frame
/// 
/// Now that we've done that, we can override the base class `void Update()` and `void Draw()`!
/// We just have two more pieces of housekeeping. Within the `Draw()` function, we must render the object to the current scene.
/// This is done with `myGObjPointer->Render(SceneManager::getCurrentScene()->getCurrentCamera());`
/// The SceneManager is also automatically included within the GameObject header.
/// This code will retrieve the 3D camera from the current scene and draw itself to the screen.
/// 
/// Finally, within the destructor of the object, we must make sure to delete `myGObjPointer` to prevent memory leaks!
/// 
/// # Linking It Together #
/// 
/// In order to have our object appear in our scene, we must first include `MyObject` in the header of the scene file and create a `MyObject*` pointer.
/// Within the scene's `void Initialize()` function, create a new box, and within the `void SceneEnd()` function, destroy it.
/// Congratulations! You have created a GameObject and successfully rendered it to your scene!
/// 
/// ### Creating Your Own Resources ###
/// 
/// As mentioned earlier, the GameObject we created uses only the pre-loaded assets. However, feel free to load your own!
/// Keep all resource-loading to LoadAllResources.cpp. Models must be given in the .azul format, and textures in the .tga format!
/// Remember that, while calling their respective `Load()` functions, keys must be unique to that manager. 
/// You may re-use keys across the ModelManager and TextureManager, for example, but you may not re-use keys within one manager.
/// Be sure to view the documentation for the various managers, listed here:
/// - ModelManager  
/// - ShaderManager  
/// - TextureManager  
/// - ImageManager  
/// - SpriteFontManager
/// 
/// That concludes the basic introduction. Other files will discuss Alarms, receiving key press events, factories, and much more!
///-------------------------------------------------------------------------------------------------
