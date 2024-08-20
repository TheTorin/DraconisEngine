#include "Visualizer.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManagerAttorney.h"
#include "VCommandFactory.h"
#include "VisualizerCommand.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeOBB.h"

Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Vect(0.5f, 0.5f, 1.5f, 1.5f);

Visualizer::Visualizer()
{
	vizSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ConstantColor"), DEFAULT_COLOR);
	vizBox = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Cube"), ShaderManager::Get("ConstantColor"), DEFAULT_COLOR);
}

void Visualizer::showCollisionVolume(const CollisionVolume& s, const Vect& col)
{
	s.DebugView(col);
}

void Visualizer::showBSphere(const CollisionVolumeBSphere& s, const Vect& col)
{
	Vect rad = s.GetRadius() * Vect(1, 1, 1);
	Matrix world = Matrix(SCALE, rad) * Matrix(TRANS, s.GetCenter());
	
	VisualizerCommand* cmd = VCommandFactory::CreateCommandBSphere(world, col);
	Instance().commands.push(cmd);
}

void Visualizer::showAABB(const CollisionVolumeAABB& s, const Vect& col)
{
	float scaleX = s.GetMax().X() - s.GetMin().X();
	float scaleY = s.GetMax().Y() - s.GetMin().Y();
	float scaleZ = s.GetMax().Z() - s.GetMin().Z();

	float transX = (s.GetMin().X() + s.GetMax().X()) / 2;
	float transY = (s.GetMin().Y() + s.GetMax().Y()) / 2;
	float transZ = (s.GetMin().Z() + s.GetMax().Z()) / 2;

	Vect T = Vect(transX, transY, transZ);
	Vect S = Vect(scaleX, scaleY, scaleZ);
	Matrix world = Matrix(SCALE, S) * Matrix(TRANS, T);

	VisualizerCommand* cmd = VCommandFactory::CreateCommandAABB(world, col);
	Instance().commands.push(cmd);
}

void Visualizer::showOBB(const CollisionVolumeOBB& s, const Vect& col)
{
	float scaleX = s.GetMax().X() - s.GetMin().X();
	float scaleY = s.GetMax().Y() - s.GetMin().Y();
	float scaleZ = s.GetMax().Z() - s.GetMin().Z();

	float transX = (s.GetMin().X() + s.GetMax().X()) / 2;
	float transY = (s.GetMin().Y() + s.GetMax().Y()) / 2;
	float transZ = (s.GetMin().Z() + s.GetMax().Z()) / 2;

	Vect T = Vect(transX, transY, transZ);
	Vect S = Vect(scaleX, scaleY, scaleZ);
	Matrix world = Matrix(SCALE, S) * Matrix(TRANS, T);
	world = world * s.GetWorld();

	VisualizerCommand* cmd = VCommandFactory::CreateCommandAABB(world, col);
	Instance().commands.push(cmd);
}

void Visualizer::showPoint(const Vect& pos, const Vect& col)
{
	Matrix world = Matrix(SCALE, Vect(1, 1, 1)) * Matrix(TRANS, pos);
	VisualizerCommand* cmd = VCommandFactory::CreateCommandBSphere(world, col);
	Instance().commands.push(cmd);
}

void Visualizer::showLine(const Vect& end1, const Vect& end2, const Vect& col)
{
	Vect twoPoint = (end1 - end2) * 0.5f;
	if (twoPoint.X() < 0) twoPoint = (end2 - end1) * 0.5f;
	float dist = twoPoint.mag();
	Vect scale = Vect(1, dist * 2, 1);
	Vect center = (end1 + end2) * 0.5f;
	float angleRotX = acosf(twoPoint.Y() / twoPoint.mag());
	twoPoint.set(twoPoint.X(), 0, twoPoint.Z());
	float angleRotY = acosf(twoPoint.Z() / twoPoint.mag());

	Matrix world = Matrix(SCALE, scale) * Matrix(ROT_X, angleRotX) * Matrix(ROT_Y, angleRotY) * Matrix(TRANS, center);
	VisualizerCommand* cmd = VCommandFactory::CreateCommandAABB(world, col);
	Instance().commands.push(cmd);
}

void Visualizer::ProcessCommands()
{
	while (!commands.empty())
	{
		VisualizerCommand* cmd = commands.front();
		cmd->Execute();
		VCommandFactory::RecycleCommand(cmd);
		commands.pop();
	}
}

void Visualizer::privRenderBSphere(Matrix& s, const Vect& col)
{
	vizSphere->SetWorld(s);
	vizSphere->SetColor(col);
	vizSphere->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void Visualizer::privRenderAABB(Matrix& s, const Vect& col)
{
	vizBox->SetWorld(s);
	vizBox->SetColor(col);
	vizBox->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

void Visualizer::Terminate()
{
	VCommandFactory::Terminate();
	delete Instance().vizSphere;
	delete Instance().vizBox;

	delete ptrInstance;
	ptrInstance = nullptr;
}