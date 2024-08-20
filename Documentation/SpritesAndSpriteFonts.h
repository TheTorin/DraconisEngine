///-------------------------------------------------------------------------------------------------
/// \file	DraconisEngine\SpritesAndSpriteFonts.h.
///
/// \brief	Information about sprites, spritefonts, and 2D objects
/// 
/// ### Sprites ###
/// 
/// All sprites are created with DraconisSprite.h
/// Before creating a sprite, however, a Texture and an Image must be loaded for the sprite to use.
/// 
/// \code{.cpp}
/// 		   //LoadAllResources.cpp
/// 		   TextureManager::Load("MySprite", "MySprite.tga");
/// 		   
/// 		   ImageManager::Load("MySprite", TextureManager::Get("MySprite"));
/// \endcode
/// 
/// Once that has been done, your sprite is ready to be created. Simply use:
///     MyFirstSprite = new DraconisSprite("MySprite");
/// Simply replace "MySprite" with whatever key-string you used for the ImageManager
/// In order to draw the sprite, its `Render()` function must be called within `Draw2D()`, NOT `Draw()`
/// `Draw2D()` can be overriden from the GameObject class, just like `Draw()`
/// Now that you have a sprite, you can view the DraconisSprite.h documentation to find out what you can do with it, and don't forget to delete it later.
/// 
/// ### Sprite Fonts ###
/// 
/// Spritefonts, as the name implies, are fonts made up entirely of sprites. The current spritefont images and data are created using the SpriteFont2 program.
/// To load in a new spritefont, call the SpriteFontManager within LoadAllResources.cpp
///     SpriteFontManager::Load("ComicSans", "ComicSans.tga");
/// A .tga file and a .xml file containing that data must be within the Assets folder, and they must have the same name!
/// 
/// Now that the spritefont has been loaded in, it can be used anywhere by...
/// 
/// ### Sprite Strings ###
/// 
/// Sprite strings are the best way to render text of any kind. Simply view the documentation of SpriteString.h to see what you can do.
/// It's important to note that, unlike the ScreenLog (covered in DebugTools documentation), the SpriteString takes a std::string, and does not have functionality similar to printf
///-------------------------------------------------------------------------------------------------
