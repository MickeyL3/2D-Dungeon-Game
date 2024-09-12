#include "Room.h"

Room::Room(TArray<AnimatedSprite*>* WallSprites, TArray<Door*>* Doors, TArray<Enemy*>* Enemies, Zombie* zombie)
{
    this->WallSprites = WallSprites;
    this->Doors = Doors;
    this->Enemies = Enemies;
    this->zombie = zombie;
    this->boss = boss;    
}

Room::Room(TArray<AnimatedSprite*>* WallSprites, TArray<Door*>* Doors, TArray<Enemy*>* Enemies, Boss* boss)
{
    this->WallSprites = WallSprites;
    this->Doors = Doors;
    this->Enemies = Enemies;
}

Room::~Room()
{
}

void Room::Tick(float fElapsedTime)
{
    
    for (int Idx = 0; Idx < Enemies->Num(); Idx++)
    {
        if (Enemies->IsValidIndex(Idx))
        {
            Enemies->GetElement(Idx)->Tick(fElapsedTime);
        }
    }

    if (zombie != nullptr)
    {
        zombie->Tick(fElapsedTime);
    }
    
    if (Enemies->GetElement(0)->IsDead() && Enemies->GetElement(1)->IsDead()
        && Enemies->GetElement(2)->IsDead() && (boss != nullptr))
    {
        boss->Tick(fElapsedTime);
    }
}

void Room::Draw(float fElapsedTime)
{
    for (int x = 0; x < SCREEN_WIDTH; x += TILE_HEIGHT)
    {
        olc::vi2d topPos = olc::vi2d(x, 0);
        olc::vi2d botPos = olc::vi2d(x, SCREEN_HEIGHT - TILE_HEIGHT);
        int type = rand() % (WallSprites->Num());
        WallSprites->GetElement(type)->DrawAt(fElapsedTime, topPos);
        WallSprites->GetElement(type)->DrawAt(fElapsedTime, botPos);
    }
    for (int y = 0; y < SCREEN_HEIGHT; y += TILE_HEIGHT)
    {
        olc::vi2d leftPos = olc::vi2d(0, y);
        olc::vi2d rightPos = olc::vi2d(SCREEN_WIDTH - TILE_WIDTH, y);
        int type = rand() % (WallSprites->Num());
        WallSprites->GetElement(type)->DrawAt(fElapsedTime, leftPos);
        WallSprites->GetElement(type)->DrawAt(fElapsedTime, rightPos);
    }

    for (int Idx = 0; Idx < Doors->Num(); Idx++)
    {
        if (Doors->IsValidIndex(Idx))
        {
            Door* CurrentDoor = Doors->GetElement(Idx);
            CurrentDoor->Draw(fElapsedTime);
        }
    }

    for (int Idx = 0; Idx < Enemies->Num(); Idx++)
    {
        if (Enemies->IsValidIndex(Idx))
        {
            Enemies->GetElement(Idx)->Draw(fElapsedTime);
        }
    }

    if (zombie != nullptr)
    {
        zombie->Draw(fElapsedTime);
    }


    if (Enemies->GetElement(0)->IsDead() && Enemies->GetElement(1)->IsDead()
        && Enemies->GetElement(2)->IsDead() && (boss != nullptr))
    {
        boss->Draw(fElapsedTime);
    }
}
