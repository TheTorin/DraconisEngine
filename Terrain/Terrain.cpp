#include "Terrain.h"
#include "TextureTGA.h"
#include "ShaderManager.h"
#include "Color.h"
#include "Visualizer.h"
#include "CollisionVolumeAABB.h"
#include "DragonMath.h"
#include "GameObject.h"

int Terrain::TexelIndex(int i, int j) const
{
	return pixel_width * (j * pixPerSide + i);
}

int Terrain::PixelIndex(int i, int j) const
{
	return (j * pixPerSide) + i;
}

int Terrain::TriIndex(int i, int j) const
{
	if (i == pixPerSide) return TriIndex(i - 1, j);
	else if (j == pixPerSide) return TriIndex(i, j - 1) + 1;
	else 
	{
		int sqPerSide = pixPerSide - 1;
		return ((j * sqPerSide) + i) * 2;
	}
}

int Terrain::CellIndex(int i, int j) const
{
	int cellPerSide = pixPerSide - 1;
	return (j * cellPerSide) + i;
}

Terrain::Terrain(const char* heightmapPath, float sideLen, float maxHeight, float baseY, Texture* texture, int uRepeat, int vRepeat)
{
	int imgWidth, imgHeight, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(heightmapPath, &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgWidth == imgHeight && imgWidth != 0);

	pixel_width = 3;
	pixPerSide = imgWidth;

	int numVerts = imgWidth * imgWidth;
	pVerts = new VertexStride_VUN[numVerts];

	int nTri = ((imgWidth - 1) * (imgWidth - 1)) * 2;
	tList = new TriangleIndex[nTri];

	yOffset = baseY;
	sideLength = sideLen;
	float start = 0.5f * sideLen;
	startCorner = start;
	float inc = sideLen / (imgWidth - 1);
	widthPerCell = inc;
	float scale = 255 / maxHeight;
	scale;
	float UInc = (float)uRepeat / (float)(imgWidth - 1);
	float VInc = (float)vRepeat / (float)(imgWidth - 1);

	//Setting initial data (UV index, position, e.t.c)
	for (int i = 0; i < imgWidth; i++)
	{
		//This is each row
		int pSide = i * imgWidth;
		float pInc = i * inc;
		float VLoc = VInc * i;
		for (int k = 0; k < imgWidth; k++)
		{
 			unsigned char height = static_cast<unsigned char>(imgData[TexelIndex(k, i)]);
			float yNorm;
			if (i == 0 || k == 0 || i == imgWidth - 1|| k == imgWidth - 1) yNorm = 1;
			else yNorm = 0;
			pVerts[pSide + k].set(
				start - (inc * k),
				height / scale,
				(-start) + pInc,
				UInc * k,
				VLoc,
				0, yNorm, 0
			);
		}
	}

	//Setting triangle info
	int currPix = 0;
	for (int i = 0; i < nTri; i += 2)
	{
		if ((currPix + 1) % imgWidth == 0) currPix++;
		tList[i].set(currPix, currPix + 1, currPix + 1 + imgWidth);
		tList[i + 1].set(currPix, currPix + imgWidth + 1, currPix + imgWidth);
		currPix++;
	}
	
	//Setting normal info
	normalList = new Vect[numVerts];
	for (int i = 0; i < imgWidth; i++)
	{
		for (int k = 0; k < imgWidth; k++)
		{
			int currIndex = i * imgWidth + k;
			if (pVerts[currIndex].ny == 0)
			{
				float currX = pVerts[currIndex].x;
				float currY = pVerts[currIndex].y;
				float currZ = pVerts[currIndex].z;

				Vect up = Vect(
					pVerts[currIndex + imgWidth].x - currX,
					pVerts[currIndex + imgWidth].y - currY,
					pVerts[currIndex + imgWidth].z - currZ
				);
				Vect left = Vect(
					pVerts[currIndex - 1].x - currX,
					pVerts[currIndex - 1].y - currY,
					pVerts[currIndex - 1].z - currZ
				);
				Vect downLeft = Vect(
					pVerts[currIndex - 1 - imgWidth].x - currX,
					pVerts[currIndex - 1 - imgWidth].y - currY,
					pVerts[currIndex - 1 - imgWidth].z - currZ
				);
				Vect down = Vect(
					pVerts[currIndex - imgWidth].x - currX,
					pVerts[currIndex - imgWidth].y - currY,
					pVerts[currIndex - imgWidth].z - currZ
				);
				Vect right = Vect(
					pVerts[currIndex + 1].x - currX,
					pVerts[currIndex + 1].y - currY,
					pVerts[currIndex + 1].z - currZ
				);
				Vect upRight = Vect(
					pVerts[currIndex + 1 + imgWidth].x - currX,
					pVerts[currIndex + 1 + imgWidth].y - currY,
					pVerts[currIndex + 1 + imgWidth].z - currZ
				);

				Vect n1 = up.cross(left);
				Vect n2 = left.cross(downLeft);
				Vect n3 = downLeft.cross(down);
				Vect n4 = down.cross(right);
				Vect n5 = right.cross(upRight);
				Vect n6 = upRight.cross(up);

				Vect norm = (n1 + n2 + n3 + n4 + n5 + n6) * (1.0f / 6.0f);
				norm.norm();

				normalList[currIndex] = norm;
			}
		}
	}
	
	//Setting info for all cells
	int cubeSide = imgWidth - 1;
	cellList = new Cell[cubeSide * cubeSide];
	cellAABBList = new CellAABB[cubeSide * cubeSide];

	for (int y = 0; y < cubeSide; y++)
	{
		for (int x = 0; x < cubeSide; x++)
		{
			cellList[(y * cubeSide) + x].indX = x;
			cellList[(y * cubeSide) + x].indY = y;
			float currMin = pVerts[PixelIndex(x, y)].y;
			float currMax = currMin;

			float currY = pVerts[PixelIndex(x + 1, y)].y;
			if (currY > currMax) currMax = currY;
			else if (currY < currMin) currMin = currY;

			currY = pVerts[PixelIndex(x, y + 1)].y;
			if (currY > currMax) currMax = currY;
			else if (currY < currMin) currMin = currY;

			currY = pVerts[PixelIndex(x + 1, y + 1)].y;
			if (currY > currMax) currMax = currY;
			else if (currY < currMin) currMin = currY;

			cellList[(y * cubeSide) + x].maxY = currMax;
			cellList[(y * cubeSide) + x].minY = currMin;

			Vect min = Vect(pVerts[PixelIndex(x + 1, y)].x, currMin + yOffset, pVerts[PixelIndex(x + 1, y)].z);
			Vect max = Vect(pVerts[PixelIndex(x, y + 1)].x, currMax + yOffset, pVerts[PixelIndex(x, y + 1)].z);

			cellAABBList[(y * cubeSide) + x].min = min;
			cellAABBList[(y * cubeSide) + x].max = max;
		}
	}

	terrainMod = new Model(pVerts, numVerts, tList, nTri);

	pTerrain = new GraphicsObject_TextureFlat(terrainMod, ShaderManager::Get("ObjTex"), texture);
	Vect col = Vect(1, 1, 1);
	pWireframe = new GraphicsObject_WireframeConstantColor(terrainMod, ShaderManager::Get("ConstantColor"), col);

	worldMat = Matrix(IDENTITY) * Matrix(TRANS, Vect(0, baseY, 0));

	pTerrain->SetWorld(worldMat);
	pWireframe->SetWorld(worldMat);

	delete[] pVerts;
	delete[] tList;
}

void Terrain::Draw(Camera* c)
{
	pTerrain->Render(c);
	pWireframe->Render(c);
}

int Terrain::PosToCellIndex(float x, float z) const
{
	float cellPerSide = pixPerSide - 1.0f;
	float relX = -x / widthPerCell;
	int resultX = (int)floor(relX + (cellPerSide / 2.0f));
	float relY = z / widthPerCell;
	int resultY = (int)floor(relY + (cellPerSide / 2.0f));

	resultX = (int)DragonMath::Clamp((float)resultX, 0, cellPerSide - 1);
	resultY = (int)DragonMath::Clamp((float)resultY, 0, cellPerSide - 1);

	return CellIndex(resultX, resultY);
}

int Terrain::PosToCellIndexCeil(float x, float z) const
{
	float cellPerSide = pixPerSide - 1.0f;
	float relX = -x / widthPerCell;
	int resultX = (int)ceil(relX + (cellPerSide / 2.0f));
	float relY = z / widthPerCell;
	int resultY = (int)ceil(relY + (cellPerSide / 2.0f));

	resultX = (int)DragonMath::Clamp((float)resultX, 0, cellPerSide - 1);
	resultY = (int)DragonMath::Clamp((float)resultY, 0, cellPerSide - 1);

	return CellIndex(resultX, resultY);
}

void Terrain::Highlight(float x, float y)
{
	int ind = PosToCellIndex(x, y);
	Cell toHighlight = cellList[ind];

	float minX = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX + 1, toHighlight.indY)].X();
	float minZ = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX + 1, toHighlight.indY)].Z();
	float maxX = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX, toHighlight.indY + 1)].X();
	float maxZ = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX, toHighlight.indY + 1)].Z();

	Vect min = Vect(minX, toHighlight.minY + yOffset, minZ);
	Vect max = Vect(maxX, toHighlight.maxY + yOffset, maxZ);

	CollisionVolumeAABB h;
	h.SetData(min, max);
	Visualizer::showAABB(h);
}

void Terrain::HighlightAll(GameObject* m)
{
	float rad = m->GetDefaultSphere()->GetRadius();
	float x = m->GetDefaultSphere()->GetCenter().X();
	float z = m->GetDefaultSphere()->GetCenter().Z();
	int minIndex = PosToCellIndex(x + rad, z - rad);
	int maxIndex = PosToCellIndexCeil(x - rad, z + rad);
	
	int distX = cellList[maxIndex].indX - cellList[minIndex].indX;
	int distY = cellList[maxIndex].indY - cellList[minIndex].indY;

	int currIndex = minIndex;
	CollisionVolumeAABB h;

	Vect min = Vect(x - rad, -200, z - rad);
	Vect max = Vect(x + rad, 200, z + rad);

	h.SetData(min, max);
	Visualizer::showAABB(h, Color::LightGray);

	Cell toHighlight;

	for (int i = 0; i < distY; i++)
	{
		for (int k = 0; k < distX; k++)
		{
			toHighlight = cellList[currIndex];

			float minX = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX + 1, toHighlight.indY)].X();
			float minZ = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX + 1, toHighlight.indY)].Z();
			float maxX = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX, toHighlight.indY + 1)].X();
			float maxZ = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX, toHighlight.indY + 1)].Z();

			min = Vect(minX, toHighlight.minY + yOffset, minZ);
			max = Vect(maxX, toHighlight.maxY + yOffset, maxZ);

			h.SetData(min, max);
			Visualizer::showAABB(h, Color::Yellow);

			currIndex++;
		}
		currIndex += (pixPerSide - 1) - distX;
	}
}

//void Terrain::Intersect(GameObject* m)
//{
//	float rad = m->GetDefaultSphere()->GetRadius();
//	float x = m->GetDefaultSphere()->GetCenter().X();
//	float y = m->GetDefaultSphere()->GetCenter().Y();
//	float z = m->GetDefaultSphere()->GetCenter().Z();
//	int minIndex = PosToCellIndex(x + rad, z - rad);
//	int maxIndex = PosToCellIndexCeil(x - rad, z + rad);
//
//	int distX = cellList[maxIndex].indX - cellList[minIndex].indX;
//	int distY = cellList[maxIndex].indY - cellList[minIndex].indY;
//
//	int currIndex = minIndex;
//	CollisionVolumeAABB h;
//
//	Vect min = Vect(x - rad, y - rad, z - rad);
//	Vect max = Vect(x + rad, y + rad, z + rad);
//
//	h.SetData(min, max);
//	Visualizer::showAABB(h, Color::LightGray);
//
//	Cell toHighlight;
//
//	for (int i = 0; i < distY; i++)
//	{
//		for (int k = 0; k < distX; k++)
//		{
//			toHighlight = cellList[currIndex];
//
//			float minX = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX + 1, toHighlight.indY)].X();
//			float minZ = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX + 1, toHighlight.indY)].Z();
//			float maxX = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX, toHighlight.indY + 1)].X();
//			float maxZ = pWireframe->getModel()->getVectList()[PixelIndex(toHighlight.indX, toHighlight.indY + 1)].Z();
//
//			min = Vect(minX, toHighlight.minY + yOffset, minZ);
//			max = Vect(maxX, toHighlight.maxY + yOffset, maxZ);
//
//			h.SetData(min, max);
//
//			Visualizer::showBSphere(*m->GetDefaultSphere());
//			if (DragonMath::Intersect(*m->GetDefaultSphere(), h))
//			{
//				Visualizer::showCollisionVolume(*m->GetCollisionVolume());
//				if (DragonMath::Intersect(*m->GetCollisionVolume(), h))
//				{
//					Visualizer::showAABB(h, Color::Red);
//				}
//				else
//				{
//					Visualizer::showAABB(h, Color::Yellow);
//				}
//			}
//			else
//			{
//				Visualizer::showAABB(h, Color::Green);
//			}
//
//			currIndex++;
//		}
//		currIndex += (pixPerSide - 1) - distX;
//	}
//}

float Terrain::GetHeight(GameObject* m)
{
	return GetHeight(m->GetDefaultSphere()->GetCenter().X(), m->GetDefaultSphere()->GetCenter().Z());
}

float Terrain::GetHeight(float x, float z)
{
	int ind = PosToCellIndex(x, z);
	Cell over = cellList[ind];
	Vect* list = pWireframe->getModel()->getVectList();
	
	Vect a = Vect(list[PixelIndex(over.indX, over.indY)].X(), 0, list[PixelIndex(over.indX, over.indY)].Z());
	Vect p = Vect(x, 0, z);

	float xBeta = (-(p - a).X()) / widthPerCell;
	float zBeta = (p - a).Z() / widthPerCell;

	float cHeight = list[PixelIndex(over.indX + 1, over.indY + 1)].Y();
	float aHeight = list[PixelIndex(over.indX, over.indY)].Y();
	float bHeight;
	float pHeight;
	if (-(p - a).X() > (p - a).Z())
	{
		bHeight = list[PixelIndex(over.indX + 1, over.indY)].Y();
		pHeight = aHeight + (xBeta * (bHeight - aHeight)) + (zBeta * (cHeight - bHeight));
	}
	else
	{
		bHeight = list[PixelIndex(over.indX, over.indY + 1)].Y();
		pHeight = aHeight + (zBeta * (bHeight - aHeight)) + (xBeta * (cHeight - bHeight));
	}

	return pHeight + yOffset;
}

Vect Terrain::GetNormal(GameObject* m)
{
	return GetNormal(m->GetDefaultSphere()->GetCenter().X(), m->GetDefaultSphere()->GetCenter().Z());
}

Vect Terrain::GetNormal(float x, float z)
{
	int ind = PosToCellIndex(x, z);
	Cell over = cellList[ind];

	Vect a = Vect(pWireframe->getModel()->getVectList()[PixelIndex(over.indX, over.indY)].X(), 0, pWireframe->getModel()->getVectList()[PixelIndex(over.indX, over.indY)].Z());
	Vect p = Vect(x, 0, z);

	float xBeta = (-(p - a).X()) / widthPerCell;
	float zBeta = (p - a).Z() / widthPerCell;

	Vect cNorm = normalList[PixelIndex(over.indX + 1, over.indY + 1)];
	Vect aNorm = normalList[PixelIndex(over.indX, over.indY)];
	Vect bNorm;
	Vect pNorm;
	if (-(p - a).X() > (p - a).Z())
	{
		bNorm = normalList[PixelIndex(over.indX + 1, over.indY)];
		pNorm = aNorm + (xBeta * (bNorm - aNorm)) + (zBeta * (cNorm - bNorm));
	}
	else
	{
		bNorm = normalList[PixelIndex(over.indX, over.indY + 1)];
		pNorm = aNorm + (zBeta * (bNorm - aNorm)) + (xBeta * (cNorm - bNorm));
	}
	return pNorm;
}

CellAABB* Terrain::GetCellFromLoc(int x, int z)
{
	int cubeSide = pixPerSide - 1;
	return &cellAABBList[(z * cubeSide) + x];
}

void Terrain::Draw()
{
	pWireframe->Render(SceneManager::getCurrentScene()->getCurrentCamera());
	pTerrain->Render(SceneManager::getCurrentScene()->getCurrentCamera());
}

Terrain::~Terrain()
{
	delete[] normalList;
	delete[] cellList;
	delete[] cellAABBList;
	delete terrainMod;
	delete pTerrain;
	delete pWireframe;
}