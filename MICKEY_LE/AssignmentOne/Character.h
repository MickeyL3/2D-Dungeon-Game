#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include"AnimatedSprite.h"
#include "Actor.h"

class Character : public Actor 
{
public:
    Character(const TVector2D<int>& position, int health, int damage);
    virtual ~Character();
    int GetHealth() const;
    void SetHealth(int health);
    int GetDamage() const;
    void SetDamage(int damage);
    void SetSprite(AnimatedSprite* newSprite);
    virtual void Tick(float fElapsedTime) override;
    virtual void Draw(float fElapsedTime) override;
    virtual void TakeDamage(int amount);
    virtual void Die();
    bool IsDead() const;

protected:
    int Health = 0;
    int Damage = 0;
    bool gameOver = false;
    AnimatedSprite* sprite;
};

#endif // CHARACTER_H