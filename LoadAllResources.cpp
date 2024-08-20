#include "Draconis.h"
#include "SceneManager.h"
#include "..//User Code/FirstScene.h"
#include "..//User Code/Menu.h"
#include "SpriteFontManager.h"
#include "ParticleEffectManager.h"
#include "ParticleEffect.h"

void Draconis::LoadAllResources()
{
	//Engine-required resources. Key must remain the same
	ModelManager::Load("Sphere", Model::PreMadeModels::UnitSphere);
	ModelManager::Load("Cube", Model::PreMadeModels::UnitBox_WF);
	ModelManager::Load("Square", Model::PreMadeModels::UnitSquareXY);

	TextureManager::Load("Border", "Border.tga");
	TextureManager::Load("Green", 0, 0, 150);
	TextureManager::Load("Red", 255, 0, 0);
	TextureManager::Load("Blue", 0, 255, 0);
	TextureManager::Load("White", 150, 150, 150);

	ShaderManager::Load("Sprite", "spriteRender");

	SpriteFontManager::Load("Centaur", "Centaur");

	//User-defined resources
	ModelManager::Load("Axis", "Axis.azul");
	ModelManager::Load("Plane", "Plane.azul");
	ModelManager::Load("Frigate", "space_frigate.azul");
	ModelManager::Load("TankBody", "Tank_Body2.azul");
	ModelManager::Load("TankTurret", "Tank_Turret2.azul");
	ModelManager::Load("TankBarrel", "Tank_Barrel2.azul");
	ModelManager::Load("Tank", "Panther_fbx.azul");
	ModelManager::Load("Cottage", "Cottage.azul");
	ModelManager::Load("Apartment", "UrbanBuilding.azul");

	TextureManager::Load("Frigate", "space_frigate.tga");
	TextureManager::Load("Grid", "grid.tga");
	TextureManager::Load("Grass", "Grass.tga");
	TextureManager::Load("Stitch", "stitch.tga");
	TextureManager::Load("MenuBG", "TankMenu.tga");
	TextureManager::Load("Fire", "Explosion.tga");
	TextureManager::Load("Raindrop", "Raindrop.tga");
	TextureManager::Load("Bricks", "brick-wall.tga");
	TextureManager::Load("Building", "BuildingTex.tga");
	TextureManager::Load("Firelion", "firelion_up.tga");
	TextureManager::Load("Ember", "Ember.tga");
	TextureManager::Load("Smoke", "Smoke.tga");

	ShaderManager::Load("ObjTex", "textureFlatRender");
	ShaderManager::Load("ObjTexLight", "textureLightRender");
	ShaderManager::Load("ConstantColor", "colorConstantRender");
	ShaderManager::Load("ColorNoTex", "colorNoTextureRender");
	ShaderManager::Load("ColorNoTexLight", "colorNoTextureLightRender");

	ImageManager::Load("Stitch", TextureManager::Get("Stitch"));
	ImageManager::Load("MenuBG", TextureManager::Get("MenuBG"));

	SpriteFontManager::Load("Comic Sans", "ComicSans");
	SpriteFontManager::Load("Elephant", "Elephant");
	SpriteFontManager::Load("Showcard", "Showcard");

	TerrainManager::Load("Level1", "TerrainLevelOne.tga", 10000, 1000, -100, "Grass", 15, 15);
	TerrainManager::Load("Level2", "TerrainLevelTwo.tga", 10000, 1000, -100, "Grass", 15, 15);
	TerrainManager::Load("Level3", "TerrainLevelThree.tga", 10000, 1000, -100, "Grass", 15, 15);

	GraphicsObject_TextureFlat* txt = new GraphicsObject_TextureFlat(ModelManager::Get("Square"), ShaderManager::Get("ObjTex"), TextureManager::Get("Raindrop"));
	ParticleEffectManager::Load("Rain", txt, Vect(0, -5, 0));

	GraphicsObject_TextureFlat* fire = new GraphicsObject_TextureFlat(ModelManager::Get("Square"), ShaderManager::Get("ObjTex"), TextureManager::Get("Ember"));
	ParticleEffectManager::Load("Sparks", fire, Vect(0, -10, 0));
	ParticleEffect* e = ParticleEffectManager::Get("Sparks");
	e->minSpeed = 10;
	e->maxSpeed = 15;
	e->maxBursts = 2;
	e->particleLife = 3;
	e->scaleChange = 0.5f;
	e->maxEmitAngle = MATH_PI4;
	e->scaleStart = 3;
	e->emitterLife = 1;

	GraphicsObject_TextureFlat* fire2 = new GraphicsObject_TextureFlat(ModelManager::Get("Square"), ShaderManager::Get("ObjTex"), TextureManager::Get("Ember"));
	ParticleEffectManager::Load("SparksFast", fire2, Vect(0, -10, 0));
	e = ParticleEffectManager::Get("SparksFast");
	e->minSpeed = 30;
	e->maxSpeed = 40;
	e->maxBursts = 2;
	e->particleLife = 3;
	e->maxEmitAngle = MATH_PI4;
	e->scaleStart = 3;
	e->emitterLife = 1;

	GraphicsObject_TextureFlat* smoke = new GraphicsObject_TextureFlat(ModelManager::Get("Square"), ShaderManager::Get("ObjTex"), TextureManager::Get("Smoke"));
	ParticleEffectManager::Load("SmokeTrail", smoke, Vect(0, 0, 0));
	e = ParticleEffectManager::Get("SmokeTrail");
	e->minSpeed = 10;
	e->maxSpeed = 15;
	e->maxBursts = 10;
	e->particleLife = 5;
	e->scaleStart = 10;
	e->maxEmitAngle = MATH_PI8;
	e->emitterLife = 6;

	SceneManager::setStartScene(new Menu());

	//---------------------------------------------------------------------------------------------------------
	// Shaders for future reference
	//---------------------------------------------------------------------------------------------------------

	//ShaderObject("textureFlatRender");
	//ShaderObject("textureLightRender");
	//ShaderObject("colorVaryRender");
	//ShaderObject("colorConstantRender");
	//ShaderObject("colorNoTextureRender");
	//ShaderObject("colorNoTextureLightRender");
	//ShaderObject("colorVaryRender");
	//ShaderObject("spriteRender");
	//ShaderObject("spriteLineRender");
}