#include "AnimatedSprite.h"
#include "TextureManager.h"
#include "ImageManager.h"
#include "TimeManager.h"

AnimatedSprite::AnimatedSprite(std::string path, int horSlice, int vertSlice)
{
	std::string key = path;
	path = path + ".tga";
	TextureManager::Load(key, path.c_str());
	spriteSheet = TextureManager::Get(key);

	float w = spriteSheet->getWidth() / (float)horSlice;
	float h = spriteSheet->getHeight() / (float)vertSlice;

	float x = 0;
	float y = 0;

	int counter = 1;

	reel = new Sprite*[horSlice * vertSlice];

	for (int i = 0; i < vertSlice; ++i)
	{
		for (int j = 0; j < horSlice; ++j)
		{
			std::string name = key + std::to_string(counter);
			ImageManager::Load(name, spriteSheet, new Rect(x, y, w, h));

			reel[counter - 1] = new Sprite(name);
			reel[counter - 1]->SetScalePixel(w, h);
			reel[counter - 1]->SetCenter(0, 0);

			++counter;
			x += w;
		}
		x = 0;
		y += h;
	}

	maxFrame = counter - 1;
	currentFrame = 0;

	timeBetweenFrames = 1;
	currentTime = 0;
	loop = false;
}

AnimatedSprite::Sprite* AnimatedSprite::GetFrame(int index)
{
	index = index % maxFrame;
	return reel[index];
}

void AnimatedSprite::Process()
{
	currentTime -= TimeManager::getFrameTime();
	if (currentTime <= 0)
	{
		currentTime = timeBetweenFrames;
		if (currentFrame != maxFrame)
		{
			++currentFrame;
		}
		else
		{
			//Change frames, but at max frame. Check loop status
			if (loop) currentFrame = 0;
		}
	}
}

void AnimatedSprite::ProcessAndDraw()
{
	Process();
	reel[currentFrame]->Render();
}

AnimatedSprite::~AnimatedSprite()
{
	for (int i = 0; i < maxFrame; ++i)
	{
		delete reel[i];
	}
	delete[] reel;
}