#pragma once
#ifndef DOOR_H
#define DOOR_H
#include "TVector2D.h"
#include "olcPixelGameEngine.h"
#include "AnimatedSprite.h"
#include <memory>
#include "Actor.h"

class Door : public Actor
{
public:
    Door(AnimatedSprite* lockedSprite, AnimatedSprite* unlockedSprite, bool isLocked);
    void Tick(float deltaTime) override;
    void Draw(float fElapsedTime) override;
    void SetSprite(AnimatedSprite* newSprite);
    bool IsLocked() const;
    void Unlock();
private:
    bool isLocked;
    AnimatedSprite* lockedSprite;
    AnimatedSprite* unlockedSprite;
    AnimatedSprite* sprite;
};

#endif  //DOOR_H