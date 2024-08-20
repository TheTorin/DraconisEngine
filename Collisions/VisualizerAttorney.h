#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "Visualizer.h"

class VisualizerAttorney
{
public:
	class Engine
	{
		friend class Draconis;
		friend class Scene;
	private:
		static void Terminate() { Visualizer::Terminate(); };
		static void ProcessCommands() { Visualizer::Instance().ProcessCommands(); };
	};
	class Commands
	{
		friend class VisualizerCommandAABB;
		friend class VisualizerCommandBSphere;
	private:
		static void renderBSphere(Matrix& m, const Vect& v) { Visualizer::Instance().privRenderBSphere(m, v); };
		static void renderAABB(Matrix& m, const Vect& v) { Visualizer::Instance().privRenderAABB(m, v); };
	};
};

#endif _VisualizerAttorney