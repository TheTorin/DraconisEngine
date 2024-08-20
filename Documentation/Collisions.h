///-------------------------------------------------------------------------------------------------
/// \file	DraconisEngine\Collisions.h.
///
/// \brief	Information about collisions
/// 
/// ### Registering Objects For Collision ###
/// 
/// In order to register a GameObject for collision, there are three steps that must be taken.
/// First, we need to set a Collidable group. These are user-defined classes, and you declare which group each object belongs to.
/// Keep in mind that you can check for collision within a group and between different groups.
/// Next, we must define what our collision model looks like. The easiest (and currently only) way to do this is by using the models native BSphere.
/// Both of these functions are always done within the constructor.
/// 
/// \code{.cpp}
/// 		   MyEnemy::MyEnemy()
/// 		   {
/// 		       ...
/// 		       myGObj = new GraphicsObject ...
/// 		       
/// 		       SetCollidableGroup<MyEnemy>();
/// 		       SetColliderModel(myGObj->getModel());
/// 		   }
/// \endcode
/// 
/// The final step is to actually submit for collision registration, done via `SubmitCollisionRegistration()`. 
/// This is typically done in the constructor, unless your object will be entering and exiting the scene, such as through a factory.
/// 
/// However, an objects collision data is not always the same as its position in space. This is why the `UpdateCollisionData(MyMatrix)` function exists.
/// This function must be called whenever the position of the collision sphere changes. Typically this is done whenever the object moves during `Update()`, but not always.
/// 
/// \code{.cpp}
/// 		   void MyEnemy::Update()
/// 		   {
/// 		       ...
/// 		       Matrix worldMatrix = ScaleMatrix * RotationMatrix * Matrix(TRANS, PositionVector);
/// 		       myGObj->SetWorld(worldMatrix);
/// 		       UpdateCollisionData(worldMatrix);
/// 		   }
/// \endcode
/// 
/// ### Checking For Collisions ###
/// 
/// However, the engine will not automatically check for every collision between every group. The engine must be told what collisions to check for.
/// This is done on a scene-by-scene basis, and so is controlled within the user defined Scene class.
/// Within `Initialize()`, simply use the `SetCollisionPair<T1, T2>()` or the `SetCollisionSelf<T1>()` functions to declare what collisions to check for.
/// `SetCollisionSelf<T1>()` only checks for collisions between objects of the same group. An object cannot collide with itself.
/// 
/// \code{.cpp}
/// 		   void MyScene::Initialize()
/// 		   {
/// 		       ...
/// 		       SetCollisionPair<MyEnemy, MyBullet>();
/// 		       SetCollisionSelf<MyBullet>();
/// 		   }
/// \endcode
/// 
/// ### Reacting To Collisions ###
/// 
/// When two objects collide, they will both receive a function call so that they may react to the collision.
/// The base version of this command is `virtual void Collision(Collidable* other)`. This will be called when the GameObject collides with ANYTHING it has registered for.
/// There is also the option to specify what object you are looking for.
/// 
/// \code{.h}
/// 		 //Forward declaring is the recommended way to handle specific collision functions
/// 		 class MyBullet;
/// 		 class MyEnemy
/// 		 {
/// 		 public:
/// 		     ...
/// 		     virtual void Collision(Collidable* other) { RunAway(); };
/// 		     virtual void Collision(MyBullet* other) { SubmitExit(); };
/// 		 }
/// \endcode
///-------------------------------------------------------------------------------------------------
