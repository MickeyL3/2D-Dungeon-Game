#include "AnimatedSprite.h"
#include "MonsterWorld.h"
#include<algorithm>


AnimatedSprite::AnimatedSprite(
    olc::Sprite* spriteImageData,
    EAnimationType animationType,
    FAnimSequence animationSequence)
{
    SpriteImageData = spriteImageData;
    AnimationType = animationType;
    AnimationSequence = animationSequence;
}

void AnimatedSprite::DrawAt(float fElapsedTime, olc::vi2d InScreenPosition)
{
    ElapsedTime += fElapsedTime;
    int currentFrame = 0;
    switch (AnimationType)
    {
    case EAnimationType::STILL:
        currentFrame = 0;
        break;
    case EAnimationType::LOOP_ONCE:
        currentFrame = std::min(static_cast<int>
            ((ElapsedTime / AnimationSequence.GameTimeTrack) * AnimationSequence.FramesNumber), AnimationSequence.FramesNumber - 1);
        break;
    case EAnimationType::LOOP_FOREVER:
        currentFrame = static_cast<int>((ElapsedTime / AnimationSequence.GameTimeTrack) * AnimationSequence.FramesNumber) % AnimationSequence.FramesNumber;
        break;
    }
    olc::vi2d sourcePos = AnimationSequence.FirstFrameOffset + olc::vi2d(currentFrame * (AnimationSequence.SpriteSize.x + 1), 0);
    MonsterWorld::Monster->DrawPartialSprite(InScreenPosition, SpriteImageData, sourcePos, AnimationSequence.SpriteSize);
}
