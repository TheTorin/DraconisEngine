#include "DragonMath.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "Visualizer.h"
#include "ScreenLog.h"

using namespace DragonMath;

float DragonMath::ProjectionLength(Vect projectThis, Vect ontoThis)
{
	return (projectThis.dot(ontoThis)) / ontoThis.mag();
}

Vect DragonMath::Projection(Vect projectThis, Vect ontoThis)
{
	return (projectThis.dot(ontoThis) / ontoThis.dot(ontoThis)) * ontoThis;
}

float DragonMath::Clamp(float value, float min, float max)
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

Vect DragonMath::Clamp(Vect value, Vect min, Vect max)
{
	float xClamp = Clamp(value.X(), min.X(), max.X());
	float yClamp = Clamp(value.Y(), min.Y(), max.Y());
	float zClamp = Clamp(value.Z(), min.Z(), max.Z());
	return Vect(xClamp, yClamp, zClamp);
}

bool DragonMath::Intersect(const CollisionVolume& col1, const CollisionVolume& col2)
{
	return col1.IntersectRequest(col2);
}

bool DragonMath::Intersect(const CollisionVolumeBSphere& bs1, const Vect point)
{
	Vect dist = bs1.GetCenter() - point;
	if (dist.mag() > bs1.GetRadius()) return false;
	else return true;
}

bool DragonMath::Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeBSphere& bs2)
{
	Vect minCenter = bs1.GetCenter() - bs2.GetCenter();
	float radiusTest = (bs1.GetRadius() + bs2.GetRadius()) * (bs1.GetRadius() + bs2.GetRadius());

	return (minCenter.dot(minCenter) < radiusTest);
}

bool DragonMath::Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeAABB& ab1)
{
	Vect point = Clamp(bs1.GetCenter(), ab1.GetMin(), ab1.GetMax());
	return Intersect(bs1, point);
}

bool DragonMath::Intersect(const CollisionVolumeAABB& ab1, const CollisionVolumeAABB& ab2)
{
	if (ab1.GetMax().X() < ab2.GetMin().X() || ab1.GetMin().X() > ab2.GetMax().X()) return false;
	if (ab1.GetMax().Y() < ab2.GetMin().Y() || ab1.GetMin().Y() > ab2.GetMax().Y()) return false;
	if (ab1.GetMax().Z() < ab2.GetMin().Z() || ab1.GetMin().Z() > ab2.GetMax().Z()) return false;
	return true;
}

bool DragonMath::Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeOBB& ob1)
{
	Matrix inverse = ob1.GetWorld().getInv();
	Vect Q = bs1.GetCenter() * inverse;
	Q = Clamp(Q, ob1.GetMin(), ob1.GetMax());
	Q = Q * ob1.GetWorld();
	return Intersect(bs1, Q);
}

float DragonMath::MaxProjection(const CollisionVolumeBox& ob1, Vect axis)
{
	Vect localAxis = axis * ob1.GetWorld().getInv();
	Vect diag = ob1.GetHalfDiagonal();
	float projMax = (abs(localAxis.X() * diag.X()) + abs(localAxis.Y() * diag.Y()) + abs(localAxis.Z() * diag.Z())) / axis.mag();
	return projMax * ob1.GetScaleSquared();
}

bool DragonMath::Intersect(const CollisionVolumeOBB& ob1, const CollisionVolumeOBB& ob2)
{
	Vect testNormals[15] = {
		ob1.GetWorld().get(ROW_0),
		ob1.GetWorld().get(ROW_1),
		ob1.GetWorld().get(ROW_2),
		ob2.GetWorld().get(ROW_0),
		ob2.GetWorld().get(ROW_1),
		ob2.GetWorld().get(ROW_2),
		ob1.GetWorld().get(ROW_0).cross(ob2.GetWorld().get(ROW_0)),
		ob1.GetWorld().get(ROW_0).cross(ob2.GetWorld().get(ROW_1)),
		ob1.GetWorld().get(ROW_0).cross(ob2.GetWorld().get(ROW_2)),
		ob1.GetWorld().get(ROW_1).cross(ob2.GetWorld().get(ROW_0)),
		ob1.GetWorld().get(ROW_1).cross(ob2.GetWorld().get(ROW_1)),
		ob1.GetWorld().get(ROW_1).cross(ob2.GetWorld().get(ROW_2)),
		ob1.GetWorld().get(ROW_2).cross(ob2.GetWorld().get(ROW_0)),
		ob1.GetWorld().get(ROW_2).cross(ob2.GetWorld().get(ROW_1)),
		ob1.GetWorld().get(ROW_2).cross(ob2.GetWorld().get(ROW_2)),
	};
	Vect currentTest;

	for (int i = 0; i < 15; i++)
	{
		currentTest = testNormals[i];
		if (currentTest.magSqr() > FLT_EPSILON)
		{
			currentTest.set(currentTest.X(), currentTest.Y(), currentTest.Z(), 0);
			float dist = abs((ob2.GetWorldCenter() - ob1.GetWorldCenter()).dot(currentTest)) / currentTest.mag();
			float proj1 = MaxProjection(ob1, currentTest);
			float proj2 = MaxProjection(ob2, currentTest);
			if (dist > proj1 + proj2) return false;
		}
	}
	return true;
}

bool DragonMath::Intersect(const CollisionVolumeAABB& ab1, const CollisionVolumeOBB& ob1)
{
	Vect testNormals[15] = {
	ob1.GetWorld().get(ROW_0),
	ob1.GetWorld().get(ROW_1),
	ob1.GetWorld().get(ROW_2),
	ab1.GetWorld().get(ROW_0),
	ab1.GetWorld().get(ROW_1),
	ab1.GetWorld().get(ROW_2),
	ob1.GetWorld().get(ROW_0).cross(ab1.GetWorld().get(ROW_0)),
	ob1.GetWorld().get(ROW_0).cross(ab1.GetWorld().get(ROW_1)),
	ob1.GetWorld().get(ROW_0).cross(ab1.GetWorld().get(ROW_2)),
	ob1.GetWorld().get(ROW_1).cross(ab1.GetWorld().get(ROW_0)),
	ob1.GetWorld().get(ROW_1).cross(ab1.GetWorld().get(ROW_1)),
	ob1.GetWorld().get(ROW_1).cross(ab1.GetWorld().get(ROW_2)),
	ob1.GetWorld().get(ROW_2).cross(ab1.GetWorld().get(ROW_0)),
	ob1.GetWorld().get(ROW_2).cross(ab1.GetWorld().get(ROW_1)),
	ob1.GetWorld().get(ROW_2).cross(ab1.GetWorld().get(ROW_2)),
	};
	Vect currentTest;

	for (int i = 0; i < 15; i++)
	{
		currentTest = testNormals[i];
		if (currentTest.magSqr() > FLT_EPSILON)
		{
			currentTest.set(currentTest.X(), currentTest.Y(), currentTest.Z(), 0);
			float dist = abs((ab1.GetWorldCenter() - ob1.GetWorldCenter()).dot(currentTest)) / currentTest.mag();
			float proj1 = MaxProjection(ob1, currentTest);
			float proj2 = MaxProjection(ab1, currentTest);
			if (dist > proj1 + proj2) return false;
		}
	}
	return true;
}