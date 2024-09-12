#include "Character.h"

Character::Character(const TVector2D<int>& position, int health, int damage)
	: Actor(position), Health(health), Damage(damage), sprite(nullptr)
{
}

Character::~Character()
{
}

int Character::GetHealth() const
{
	return Health;
}

void Character::SetHealth(int health)
{
	Health = health;
}

int Character::GetDamage() const
{
	return Damage;
}

void Character::SetDamage(int damage)
{
	Damage = damage;
}

void Character::SetSprite(AnimatedSprite* newSprite)
{
	sprite = newSprite;
}

void Character::Tick(float fElapsedTime)
{
	fElapsedTime = 0.0f;
}

void Character::Draw(float fElapsedTime)
{
	if (sprite) 
	{
		olc::vi2d olcPosition(Position.X, Position.Y);
		sprite->DrawAt(fElapsedTime, olcPosition);
	}
}

void Character::TakeDamage(int amount)
{
	Health -= amount;
	if (Health <= 0) 
	{
		Die();
	}
}

void Character::Die()
{
	std::cout << "Player has died!" << std::endl;
	gameOver = true;
}

bool Character::IsDead() const
{
	return Health <= 0;

}
