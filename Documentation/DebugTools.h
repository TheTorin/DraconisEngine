///-------------------------------------------------------------------------------------------------
/// \file	DraconisEngine\DebugTools.h.
///
/// \brief	Overview of the debug tools within the engine
/// 
/// ### Screen Log Info ###
/// 
/// The first debug tool to discuss is the Screen Log. This is not included by default, so it must be manually included.
/// In order to use this tool, the `ScreenLog::Add(MyChar*)` must be used.
/// The `Add` function works with similar parameters as printf, meaning the char* ("This is test number %i", MyInt) would work
/// Every call to `Add` automatically places the string below the previous one. While there is technically no limit, the size of the screen does eventually limit it.
/// 
/// \code{.cpp}
/// 		   void MyObject::Update()
/// 		   {
/// 		       ...
/// 		       ScreenLog::Add("MyObj:");
/// 		       ScreenLog::Add("\tPos: %3.1f, %3.1f, %3.1f", MyPos[x], MyPos[y], MyPos[z]);
/// 		   }
/// \endcode
/// 
/// ### Freeze Frame ###
/// 
/// The engine also includes a FreezeFrame tool. This tool is engine-wide, so does not need to be included in ANY files.
/// The FreezeFrame tool only has two commands
/// 1. Freeze (F10)
/// 2. Single Frame (F9) 
/// 
/// Freeze will completely halt the game. For all intents, time is not moving. Alarms do not progress, Update is not called, nothing will change.
/// Single Frame will advance the game forward through one interation of its loops, progressing forward one 'frame'. It will only work if the game is frozen.
/// 
/// ### Collision Visualizer ###
/// 
/// The engine also includes a collision visualizer tool. It will work on any object. The visualizer is not automatically included, and must be manually included.
/// The function can be called at any point, even in `Update()`, and the sphere will be drawn appropriately during the `Draw()` step
/// 
/// \code{.cpp}
/// 		   void MyObject::Update()
/// 		   {
/// 		       ...
/// 		       Visualizer::showBSphere(GetBSphere(), Color::Red);
/// 		   }
/// \endcode
/// 
/// GetBSphere is a function inherent to all GameObjects. It is documented under GameObject.h
///-------------------------------------------------------------------------------------------------
