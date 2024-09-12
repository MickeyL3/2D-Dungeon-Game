#include "Zombie.h"
#include <iostream>
#include "MonsterWorld.h"

const int ZOMBIE_COUNT = 3;

Zombie::Zombie(const TVector2D<int>& position, int health, int damage)
	: Enemy(position, health, damage), timeAccumulated(0.0f), DeadSprite(nullptr), Sprite(nullptr)
{
	std::cout << "Zombie created" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << "Zombie destroyed" << std::endl;
}

void Zombie::SetSprite(AnimatedSprite* sprite)
{
	Sprite = sprite;
}

void Zombie::Tick(float fElapsedTime)
{
	if (IsDead()) 
	{
		ZombieMode = DIE;
		return;
	}
	Enemy::Tick(fElapsedTime);
}

void Zombie::Draw(float fElapsedTime)
{
	olc::vi2d olcPosition(Position.X, Position.Y);
	if (ZombieMode == IDLE)
	{
		Sprite->DrawAt(fElapsedTime, olcPosition);
	}
	else if (ZombieMode == DIE)
	{
		DeadSprite->DrawAt(fElapsedTime, olcPosition);
	}
}

void Zombie::SetDeadSprite(AnimatedSprite* newSprite)
{
	DeadSprite = newSprite;
}

bool Zombie::IsDead() const
{
	return Health <= 0;
}

void Zombie::TakeDamage(int damage)
{
	std::cout << "Zombie takes " << damage << " damage!" << std::endl;
	if (Health > 0)
	{
		Health -= damage;
	}
	else
	{
		Health = 0;
	}
}

void Zombie::Move(float fElapsedTime)
{
	timeAccumulated += fElapsedTime;
	if (timeAccumulated >= 0.005f) {
		timeAccumulated = 0.0f;
		Position.X = rand() % (SCREEN_WIDTH - 24);
		Position.Y = rand() % (SCREEN_HEIGHT - 36);
	}	
}
