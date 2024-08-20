///-------------------------------------------------------------------------------------------------
/// \file	DraconisEngine\Factories.h.
///
/// \brief	Information about constructing factories and having objects enter/exit a scene
/// 
/// Not every object will stay in a scene for the entire time. Some objects, like bullets, will pop in and out.
/// Extra care must be taken when coding these objects. Some functions, such as creating the model, should only be called once.
/// Others, like `SubmitUpdateRegistration`, should be called whenever the object enters the scene.
/// This is why GameObjects have the `SubmitEntry()` and `SubmitExit()` functions, as well as `SceneEnter()` and `SceneExit()` functions
/// 
/// The `SubmitEntry()` function should never be called from the object itself. This function is requesting entry to the scene, and if an object called it, it must be in the scene.
/// So, `SubmitEntry()` must be called by an outside source, such as a factory.
/// 
/// \code{.cpp}
/// 		   void MyFactory::CreateBullet()
/// 		   {
/// 		       Bullet* b = MyPool.GetBullet();
/// 		       
/// 		       b->SubmitEntry();
/// 		   }
/// \endcode
/// 
/// This places a request command in the scene, and the object will enter the scene on the following frame.
/// As soon as it enters the scene, that object's `SceneEntry()` function will be called, allowing you to override it and place all registration commands within it.
/// Here, the distinction must be drawn between what to place in the constructor and what to place in `SceneEntry()`. Permanent, or one-time initializations, should go in the constructor.
/// ALL registrations should be placed within `SceneEntry()`, so that the object is not called while it does not exist.
/// 
/// \code{.cpp}
/// 		   MyBullet::MyBullet()
/// 		   {
/// 		       //All of these are only set once. They will not change across instances of the object
/// 			   myGObj = new Graphics_Object...
/// 		       SetCollidableGroup<MyBullet>();
/// 		       SetCollisionModel(myGObj->getModel());
/// 		   }
/// 		   
/// 		   void MyBullet::SceneEntry()
/// 		   {
/// 		       //These are registrations, and should be kept here. We also reset any important values that each instance needs to track seperately.
/// 		       SubmitUpdateRegistration();
/// 		       SubmitDrawRegistration();
/// 		       SubmitCollisionRegistration();
/// 		       PositionVector.Set(0.0f, 0.0f, 0.0f);
/// 		   }
/// \endcode
/// 
/// By contrast, `SubmitExit()` CAN be called by the object itself, or by another entity. This function works in a similar way to `SubmitEntry()`.
/// On the following frame, the command will be executed and `SceneExit()` will be called immediately.
/// `SceneExit()` should deregister ALL registrations, including alarms that may or may not be active. Calling deregistration on an inactive alarm is allowed.
/// 
/// \code{.cpp}
/// 		   void MyBullet::SceneExit()
/// 		   {
/// 		       SubmitUpdateDeregistration();
/// 		       SubmitDrawDeregistration();
/// 		       SubmitCollisionDeregistration();
/// 		       SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
/// 		       
/// 		       //If using a factory, this is also the perfect time to recycle the object
/// 		       MyFactory::RecycleBullet(this);
/// 		   }
/// \endcode
///-------------------------------------------------------------------------------------------------
