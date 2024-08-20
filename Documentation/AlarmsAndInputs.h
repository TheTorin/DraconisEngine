///-------------------------------------------------------------------------------------------------
/// \file	DraconisEngine\AlarmsAndInputs.h.
///
/// \brief	An overview of Alarms and Inputs within the engine
/// 
/// This guide assumes that you already have a GameObject created, as discussed in "Intro.h"
/// 
/// ### Alarms ###
/// 
/// With this engine, each GameObject has three unique alarms. These alarms are `void Alarm0()`, `void Alarm1()`, and `void Alarm2()`
/// These functions must be overriden in the header file.
/// However, in order to have the engine call them, the engine needs to know which alarm to call, and when to call it.
/// This is done with `SubmitAlarmRegistration(AlarmableManager::AlarmNumber, float time);`
/// The AlarmNumber is an enum within the AlarmableManager (which is automatically included), and gives the option of which alarm to call. Time is given in seconds.
/// IMPORTANT: Do not call `SubmitAlarmRegistration` on the same alarm multiple times before time is up. Doing so will cause an assert() error.
/// IMPORTANT: If your GameObject might not be present on the scene when the alarm is called (such as through factories), be sure to call `SubmitAlarmDeregistration` on the appropriate alarm.
/// Unlike registration, called deregistration on an alarm that is not registered will not cause an assert() error, so it is safe to call.
/// 
/// \code{.cpp}
/// 		   MyObject::MyObject()
/// 		   {
/// 		       ...
/// 		       SubmitAlarmRegistration(AlarmableManager::ALARM_0, 3.0f) //Calls Alarm0() after 3 seconds
/// 		   }
/// 		   
/// 		   void MyObject::Alarm0()
/// 		   {
/// 		       //Causes the object to exit the scene. We do not need to call 'SubmitAlarmDeregistration' here, as the alarm has already expired
/// 		       SubmitExit()
/// 		   }
/// \endcode
/// 
/// ### INPUTS ###
/// 
/// The inputs within this engine use the AZUL_KEY enum for all keys. If the desired key is not within this enum, the engine will not recognize it.
/// Each object can register for as many keys as they desire, and each object can register for multiple events on the same key. 
/// However, attempting to register the same key-event pair multiple times will result in an assert() error.
/// 
/// Each key has four events associated with it, given by the EventType::EVENT enum (automatically included)
/// The events are KeyPressed, KeyHeldDown, KeyReleased, and KeyHeldUp. The Inputable class has functions for each event, and has an more in-depth explanation on the SubmitInputRegistration documentation.
/// To register for an event, the SubmitInputRegistration(AZUL_KEY k, EventType e) function must be called.
/// IMPORTANT: If you GameObject might not be present on the scene when the alarm is called (such as through factories), be sure to call SubmitInputDeregistration on all key-event pairs
/// 
/// \code{.cpp}
/// 		   MyObject::MyObject()
/// 		   {
/// 		       ...
/// 		       SubmitInputRegistration(AZUL_KEY::KEY_W, EventType::KEY_PRESSED);
/// 		       SubmitInputRegistration(AZUL_KEY::KEY_W, EventType::KEY_RELEASED);
/// 		       SubmitInputRegistration(AZUL_KEY::KEY_A, EventType::Key_RELEASED);
/// 		   }
/// 		   
/// 		   void MyObject::KeyPressed(AZUL_KEY k)
/// 		   {
/// 		       //While this isn't necessary, since it will only be called if the key is W, it is still good practice to check
/// 		       if (k == AZUL_KEY::KEY_W)
/// 		       {
/// 		           ...
/// 		       }
/// 		   }
/// 		   
/// 		   void MyObject::KeyReleased(AZUL_KEY k)
/// 		   {
/// 		       if (k == AZUL_KEY::KEY_W)
/// 		       {
/// 		           ...
/// 		       }
/// 		       else if (k == AZUL_KEY::KEY_A)
/// 		       {
/// 		           ...
/// 		       }
/// 		   }
/// \endcode
///-------------------------------------------------------------------------------------------------
