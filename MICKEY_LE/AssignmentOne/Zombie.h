#pragma once
#include "Enemy.h"
#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie : public Enemy 
{
public:
    Zombie(const TVector2D<int>& position, int health, int damage);
    virtual ~Zombie();
    void SetSprite(AnimatedSprite* sprite);
    virtual void Tick(float fElapsedTime) override;
    virtual void Draw(float fElapsedTime) override;
    void SetDeadSprite(AnimatedSprite* newSprite);
    bool IsDead() const;
    void TakeDamage(int damage);
protected:
    virtual void Move(float fElapsedTime);
private:
    AnimatedSprite* Sprite;
    float timeAccumulated = 0.0f;
    AnimatedSprite* DeadSprite;
    typedef enum 
    {
        IDLE,
        DIE
    } mode_t;
    mode_t ZombieMode = IDLE;
};
#endif // !ZOMBIE_H