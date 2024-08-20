#ifndef _DraconisSprite
#define _DraconisSprite

#include "AzulCore.h"
#include <string>

class DraconisSprite
{
private:
	GraphicsObject_Sprite* pGOSprite;

	Matrix Scale;
	Matrix ZRot;
	Vect Pos;

	float angle;
	float centerX;
	float centerY;
	float scaleX;
	float scaleY;

public:
	DraconisSprite() = default;
	DraconisSprite(const std::string& key);
	DraconisSprite(const DraconisSprite&) = delete;
	DraconisSprite& operator=(const DraconisSprite&);
	~DraconisSprite();

	///-------------------------------------------------------------------------------------------------
	/// \fn	float DraconisSprite::GetWidth()
	///
	/// \brief	Gets the width of the sprite after scaling
	///
	/// \returns	The width.
	///-------------------------------------------------------------------------------------------------

	float GetWidth() { return pGOSprite->origWidth * scaleX; };

	///-------------------------------------------------------------------------------------------------
	/// \fn	float DraconisSprite::GetHeight()
	///
	/// \brief	Gets the height of the sprite after scaling
	///
	/// \returns	The height.
	///-------------------------------------------------------------------------------------------------

	float GetHeight() { return pGOSprite->origHeight * scaleY; };
	///-------------------------------------------------------------------------------------------------
	/// \fn	float DraconisSprite::GetAngle()
	///
	/// \brief	Gets the angle the sprite is rotated by
	///
	/// \returns	The angle.
	///-------------------------------------------------------------------------------------------------

	float GetAngle() { return angle; };

	///-------------------------------------------------------------------------------------------------
	/// \fn	void DraconisSprite::SetAngle(float a);
	///
	/// \brief	Sets an angle the sprite is rotated by
	///
	/// \param 	a	The angle.
	///-------------------------------------------------------------------------------------------------

	void SetAngle(float a);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void DraconisSprite::SetCenter(float offsetX, float offsetY);
	///
	/// \brief	Sets the center of the sprite
	///
	/// \param 	offsetX	The offset x coordinate.
	/// \param 	offsetY	The offset y coordinate.
	///-------------------------------------------------------------------------------------------------

	void SetCenter(float offsetX, float offsetY);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void DraconisSprite::SetPosition(float x, float y);
	///
	/// \brief	Sets a position for the sprite to appear in
	///
	/// \param 	x	The x coordinate.
	/// \param 	y	The y coordinate.
	/// 
	/// The position given is where the center of the sprite will appear. To change the center, see SetCenter()
	///-------------------------------------------------------------------------------------------------

	void SetPosition(float x, float y);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void DraconisSprite::SetScaleFactor(float scaleX, float scaleY);
	///
	/// \brief	Sets scale of the sprite
	///
	/// \param 	scaleX	The scale along the x coordinate.
	/// \param 	scaleY	The scale along the y coordinate.
	///-------------------------------------------------------------------------------------------------

	void SetScaleFactor(float sX, float sY);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void DraconisSprite::SetScalePixel(float width, float height);
	///
	/// \brief	Sets the height and width of the sprite
	///
	/// \param 	width 	The width.
	/// \param 	height	The height.
	///-------------------------------------------------------------------------------------------------

	void SetScalePixel(float width, float height);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void DraconisSprite::Render();
	///
	/// \brief	Renders the sprite to the current scene and the current 2D camera
	///-------------------------------------------------------------------------------------------------

	void Render();
};

#endif _DraconisSprite