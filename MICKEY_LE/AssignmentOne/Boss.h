#pragma once
#include "Enemy.h"
#ifndef BOSS_H
#define BOSS_H

class Boss : public Enemy 
{
public:
    Boss(const TVector2D<int>& position, int health, int damage);
    virtual ~Boss();
    void SetSprite(AnimatedSprite* sprite);
    virtual void Tick(float fElapsedTime) override;
    virtual void Draw(float fElapsedTime) override;
    void SetDeadSprite(AnimatedSprite* newSprite);
    bool IsDead() const;
    void TakeDamage(int damage);
protected:
    virtual void Move(float fElapsedTime) override;
private:
    AnimatedSprite* Sprite;
    float WaitTime = 0.0f;
    TVector2D<int> MoveDirection;
    int MoveCount = 0;
    AnimatedSprite* DeadSprite;
    typedef enum 
    {
        IDLE,
        DIE
    } mode_t;
    mode_t BossMode = IDLE;
};
#endif // BOSS_H