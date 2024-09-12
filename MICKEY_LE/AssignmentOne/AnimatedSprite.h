#pragma once
#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H
#include "olcPixelGameEngine.h"

enum class EAnimationType
{
	STILL,
	LOOP_ONCE,
	LOOP_FOREVER
};

struct FAnimSequence
{
	olc::vi2d FirstFrameOffset;
	olc::vi2d SpriteSize = {12,12};
	int FramesNumber = 4;
	float GameTimeTrack = 1.0f;
};

class AnimatedSprite
{
public:

	AnimatedSprite
	(
		olc::Sprite* spriteImageData,
		EAnimationType animationType,
		FAnimSequence animationSequence
	);
	void DrawAt(float fElapsedTime, olc::vi2d  InScreenPosition);
private:
	olc::Sprite* SpriteImageData;
	EAnimationType AnimationType;
	FAnimSequence AnimationSequence;
	float ElapsedTime = 0.0f;
};
#endif // ANIMATED_SPRITE_H