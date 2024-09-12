#include "Boss.h"
#include <iostream>
#include "MonsterWorld.h"


Boss::Boss(const TVector2D<int>& position, int health, int damage)
	: Enemy(position, health, damage), MoveCount(0), DeadSprite(nullptr), Sprite(nullptr)
{
	MoveDirection = { 0, 0 };
	std::cout << "Boss created" << std::endl;
}

Boss::~Boss()
{
	std::cout << "Boss destroyed" << std::endl;
}

void Boss::SetSprite(AnimatedSprite* sprite)
{
	Sprite = sprite;
}

void Boss::Tick(float fElapsedTime)
{
	if (IsDead()) 
	{
		BossMode = DIE;
		return;
	}
	WaitTime += fElapsedTime;
	Move(fElapsedTime);
	const int screenWidth = SCREEN_WIDTH - 36;
	const int screenHeight = SCREEN_HEIGHT - 36;

	if (Position.X < 24) Position.X = 24;
	if (Position.X > screenWidth) Position.X = screenWidth;
	if (Position.Y < 24) Position.Y = 24;
	if (Position.Y > screenHeight) Position.Y = screenHeight;
}

void Boss::Draw(float fElapsedTime)
{
	olc::vi2d olcPosition(Position.X, Position.Y);
	if (BossMode == IDLE)
	{
		Sprite->DrawAt(fElapsedTime, olcPosition);
	}
	else if (BossMode == DIE)
	{
		DeadSprite->DrawAt(fElapsedTime, olcPosition);
	}
}

void Boss::SetDeadSprite(AnimatedSprite* newSprite)
{
	DeadSprite = newSprite;

}

bool Boss::IsDead() const
{
	return Health <= 0;
}

void Boss::TakeDamage(int damage)
{
	std::cout << "Boss takes " << damage << " damage!" << std::endl;
	if (Health > 0)
	{
		Health -= damage;
	}
	else
	{
		Health = 0;
	}
}

void Boss::Move(float fElapsedTime)
{
	if (MoveCount == 0) 
	{
		int direction = rand() % 4;
		switch (direction) {

		case 0: MoveDirection = { 10, 0 }; break; 
		case 1: MoveDirection = { -10, 0 }; break; 
		case 2: MoveDirection = { 0, 10 }; break; 
		case 3: MoveDirection = { 0, -10 }; break; 
		
		}
	}
	Position += MoveDirection;
	MoveCount = (MoveCount + 1) % 10; 
	if (WaitTime >= 1.0f) 
	{
		WaitTime = 0.0f;
		MoveCount = 0; 
	}	
}