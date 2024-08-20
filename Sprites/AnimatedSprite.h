#ifndef _AnimatedSprite
#define _AnimatedSprite

#include "DraconisSprite.h"

class AnimatedSprite
{
public:
	using Sprite = DraconisSprite;

private:
	Texture* spriteSheet;
	Sprite** reel;
	int currentFrame;
	int maxFrame;

	float timeBetweenFrames;
	float currentTime;
	bool loop;

public:
	AnimatedSprite() = delete;
	AnimatedSprite(std::string path, int horizontalSprites, int verticalSprites);
	AnimatedSprite(const AnimatedSprite&) = delete;
	AnimatedSprite& operator=(const AnimatedSprite&) = delete;
	~AnimatedSprite();

	void SetTime(float time) { timeBetweenFrames = time; };
	void Loop(bool lo) { loop = lo; };

	Sprite* GetFrame(int index);

	void Process();
	void ProcessAndDraw();
};

#endif _AnimatedSprite