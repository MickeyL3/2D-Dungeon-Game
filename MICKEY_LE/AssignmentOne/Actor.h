#pragma once
#ifndef ACTOR_H
#define ACTOR_H
#include "TVector2D.h"
#include "olcPixelGameEngine.h"

class Actor
{
public:
    Actor(const TVector2D<int>& position);
    virtual ~Actor();
    virtual void Tick(float deltaTime);
    virtual void Draw(float fElapsedTime);
    void SetPosition(const TVector2D<int>& pos);
    TVector2D<int> GetPosition() const;

protected:
    TVector2D<int> Position;
};
#endif //ACTOR_H