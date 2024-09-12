#include "Actor.h"

Actor::Actor(const TVector2D<int>& position)
	: Position(position) 
{
}

Actor::~Actor()
{
	std::cout << "Actor destroyed" << std::endl;
}

void Actor::Tick(float deltaTime)
{
}

void Actor::Draw(float fElapsedTime)
{

}

void Actor::SetPosition(const TVector2D<int>& pos)
{
	Position = pos;
}

TVector2D<int> Actor::GetPosition() const
{
	return Position;
}
