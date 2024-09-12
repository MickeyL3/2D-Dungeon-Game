#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"
#include "Character.h"
#include "TVector2D.h"
#include "AnimatedSprite.h"
#include <memory>
#include "Enemy.h"
#include "infoBar.h"


class Enemy;

class Player : public Character 
{
public:
    Player(const TVector2D<int>& position, int health, int damage);
    virtual ~Player();
    void SetSprite(AnimatedSprite* newSprite);
    void SetAttackSprite(AnimatedSprite* newSprite);
    void SetDeadSprite(AnimatedSprite* newSprite);
    virtual void Tick(float fElapsedTime) override;
    virtual void Draw(float fElapsedTime) override;
    virtual void TakeDamage(int damage, InfoBar* infobar, olc::PixelGameEngine* pge, olc::Sprite* tileset);
    void Move(const TVector2D<int>& direction);
    bool isDead() const;
    void Attack(Enemy* enemy, InfoBar* infobar, olc::PixelGameEngine* pge, olc::Sprite* tileset);
    void IncreaseHealth(int amount);
    enum mode_t 
    {
        IDLE,
        ATTACK,
        DIE
    };
    enum mode_t GetPlayerMode() const;
private:
    AnimatedSprite* sprite;
    AnimatedSprite* AttackSprite;
    AnimatedSprite* DeadSprite;
    int AttackCooldown = 5;
    enum mode_t PlayerMode = IDLE;
};
#endif // PLAYER_H