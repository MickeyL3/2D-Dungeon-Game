#include "Door.h"



Door::Door(AnimatedSprite* lockedSprite, AnimatedSprite* unlockedSprite, bool isLocked)
    : Actor(TVector2D<int>(0, 0))
{
    this->lockedSprite = lockedSprite;
    this->unlockedSprite = unlockedSprite;
    this->isLocked = isLocked;

    if (isLocked)
    {
        SetSprite(lockedSprite);
    }
    else
    {
        SetSprite(unlockedSprite);
    }
}

void Door::Tick(float deltaTime)
{
}

void Door::Draw(float fElapsedTime)
{
    if (sprite) 
    {
        olc::vi2d olcPosition(Position.X, Position.Y);
        sprite->DrawAt(fElapsedTime, olcPosition); 
    }
}

void Door::SetSprite(AnimatedSprite* newSprite)
{
    sprite = newSprite;
}

bool Door::IsLocked() const
{
    return isLocked;
}

void Door::Unlock()
{
    if (isLocked) 
    {
        isLocked = false;
        SetSprite(unlockedSprite);
    }
}
