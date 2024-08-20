#include "AzulCore.h"
#include "Draconis.h"

#include "ScreenLogAttorney.h"
#include "TimeManagerAttorney.h"

#include "SpriteFontManagerAttorney.h"
#include "ImageManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "SceneManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "TerrainManagerAttorney.h"
#include "ParticleEffectManagerAttorney.h"

#include "../User Code/FirstScene.h"

// Global varables just for the demo:
// Note: Don't do this!
// Global vars should always be avoided in a finished product! 

Draconis* Draconis::ptrInstance = nullptr;

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Draconis::Initialize()
{
	GameStart();
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Draconis::LoadContent()
{
	//---------------------------------------------------------------------------------------------------------
	// Load Everything
	//---------------------------------------------------------------------------------------------------------

	LoadAllResources();

	SceneManagerAttorney::SceneManagement::initStartScene();
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Draconis::Update()
{
	TimeManagerAttorney::EngineControl::ProcessTime(this->GetTimeInSeconds());

	SceneManagerAttorney::SceneManagement::Update();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Draconis::Draw()
{
	SceneManagerAttorney::SceneManagement::Draw();

	//VisualizerAttorney::Engine::ProcessCommands();

	//SceneManagerAttorney::SceneManagement::Draw2D();
	
	ScreenLogAttorney::Engine::Render();
}


//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Draconis::UnLoadContent()
{
	GameEnd();

	ScreenLogAttorney::Engine::Terminate();
	VisualizerAttorney::Engine::Terminate();

	ParticleEffectManagerAttorney::Terminate();
	TerrainManagerAttorney::Terminate();
	SpriteFontManagerAttorney::Terminate();
	ImageManagerAttorney::Terminate();
	ModelManagerAttorney::Terminate();
	ShaderManagerAttorney::Terminate();
	TextureManagerAttorney::Terminate();
	SceneManagerAttorney::SceneManagement::Terminate();

	TimeManagerAttorney::EngineControl::Terminate();
}

void Draconis::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
