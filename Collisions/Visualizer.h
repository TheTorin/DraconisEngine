#ifndef _Visualizer
#define _Visualizer

#include "AzulCore.h"
#include <queue>

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolume;
class VisualizerCommand;
class Visualizer : public Align16
{
	friend class VisualizerAttorney;
private:
	static Visualizer* ptrInstance;

	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	~Visualizer() = default;

	static Visualizer& Instance()
	{
		if (!ptrInstance) ptrInstance = new Visualizer();
		return *ptrInstance;
	}
	
	std::queue<VisualizerCommand*> commands;

	static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* vizSphere;
	GraphicsObject_WireframeConstantColor* vizBox;

	void privRenderBSphere(Matrix& m, const Vect& col);
	void privRenderAABB(Matrix& m, const Vect& col);

	void ProcessCommands();
	static void Terminate();

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void Visualizer::showBSphere(const CollisionVolumeBSphere& s, const Vect& col = Visualizer::DEFAULT_COLOR);
	///
	/// \brief	Shows the bounding sphere
	///
	/// \param 	s  	A CollisionVolumeBSphere to process. Can be obtained with GetBSphere() for a GameObject
	/// \param 	col	(Optional) The color for the bounding sphere.
	///-------------------------------------------------------------------------------------------------

	static void showBSphere(const CollisionVolumeBSphere& s, const Vect& col = Visualizer::DEFAULT_COLOR);

	static void showAABB(const CollisionVolumeAABB& s, const Vect& col = Visualizer::DEFAULT_COLOR);

	static void showOBB(const CollisionVolumeOBB& s, const Vect& col = Visualizer::DEFAULT_COLOR);

	///----------------------
	/// \fn static void Visualizer::showCollisionVolume(const CollisionVolume& c, const Vect& col = Visualizer::DEFAULT_COLOR);
	///
	/// \brief Displays the collision volume of the object
	///
	/// \param	s	The collision volume to process. Can be obtained with GetCollisionVolume() for a GameObject
	/// \param	col	(Optional) The color for the bounding sphere.
	///----------------------

	static void showCollisionVolume(const CollisionVolume& s, const Vect& col = Visualizer::DEFAULT_COLOR);

	///----------------------
	/// \fn static void Visualizer::showPoint(const Vect& pos, const Vect& col = Visualizer::DEFAULT_COLOR);
	///
	/// \brief Draws a small box at the given point
	///
	/// \param	pos	The point where a small box will be drawn in order to represent it.
	/// \param	col	(Optional) The color for the box.
	///----------------------

	static void showPoint(const Vect& pos, const Vect& col = Visualizer::DEFAULT_COLOR);

	static void showLine(const Vect& end1, const Vect& end2, const Vect& col = Visualizer::DEFAULT_COLOR);
	
};

#endif _Visualizer