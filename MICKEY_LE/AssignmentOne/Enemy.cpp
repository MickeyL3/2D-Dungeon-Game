#include"Enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "MonsterWorld.h"

Enemy::Enemy(const TVector2D<int>& position, int health, int damage)
    : Character(position, health, damage), DeadSprite(nullptr), Sprite(nullptr)
{
    std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy()
{
    std::cout << "Enemy destroyed" << std::endl;

}

bool Enemy::IsDead() const
{
    return Health <= 0;
}

void Enemy::Tick(float fElapsedTime)
{
    if (IsDead()) 
    {
        EnemyMode = DIE;
        return;
    }
    Move(fElapsedTime);
    const int screenWidth = SCREEN_WIDTH - 24;
    const int screenHeight = SCREEN_HEIGHT - 24;

    if (Position.X < 12) Position.X = 12;
    if (Position.X > screenWidth) Position.X = screenWidth;
    if (Position.Y < 12) Position.Y = 12;
    if (Position.Y > screenHeight) Position.Y = screenHeight;
}

void Enemy::Draw(float fElapsedTime)
{
    olc::vi2d olcPosition(Position.X, Position.Y);
    if (EnemyMode == IDLE)
    {
       Sprite->DrawAt(fElapsedTime, olcPosition);
    }
    else if (EnemyMode == DIE)
    {
        DeadSprite->DrawAt(fElapsedTime, olcPosition);
    } 
}

void Enemy::SetSprite(AnimatedSprite* sprite)
{
    Sprite = sprite;
}

void Enemy::SetDeadSprite(AnimatedSprite* newSprite)
{
    DeadSprite = newSprite;
}

void Enemy::TakeDamage(int damage)
{
    std::cout << "Enemy takes " << damage << " damage!" << std::endl;
    if (Health > 0)
    {
        Health -= damage;
    }
    else
    {
        Health = 0;
    }
}

void Enemy::Reset(int health)
{
    Health = health;
    EnemyMode = IDLE;
}

void Enemy::Move(float fElapsedTime)
{
    int direction = rand() % 7;
    switch (direction) 
    {
    case 0: Position.X += 5; break; 
    case 1: Position.X -= 5; break; 
    case 2: Position.Y += 5; break; 
    case 3: Position.Y -= 5; break; 
    case 4:
    case 5:
    case 6: break; 
    }
}


