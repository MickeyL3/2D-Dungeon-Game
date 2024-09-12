#pragma once
#include "olcPixelGameEngine.h"
#ifndef ENEMY_H
#define ENEMY_H
#include "AnimatedSprite.h"
#include "TVector2D.h"
#include "Player.h"
#include "Actor.h"
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(const TVector2D<int>& position, int health, int damage);
	virtual ~Enemy();
	bool IsDead() const;
	virtual void Tick(float fElapsedTime) override;
	virtual void Draw(float fElapsedTime) override;
	void SetSprite(AnimatedSprite* sprite);
	void SetDeadSprite(AnimatedSprite* newSprite);
	void TakeDamage(int damage);
	void Reset(int health);
private:
	virtual void Move(float fElapsedTime);
	AnimatedSprite* Sprite;
	AnimatedSprite* DeadSprite;
	typedef enum 
	{
		IDLE,
		DIE
	} mode_t;
	mode_t EnemyMode = IDLE;
};
#endif // ENEMY_H