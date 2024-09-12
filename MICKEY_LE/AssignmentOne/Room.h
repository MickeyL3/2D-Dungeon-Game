#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "olcPixelGameEngine.h"
#include "MonsterWorld.h"
#include "AnimatedSprite.h"
#include "Door.h"
#include "TArray.h"
#include "Enemy.h"
#include "Zombie.h"
#include "Boss.h"

class Room
{
public:
    Room(TArray<AnimatedSprite*>* WallSprites, TArray<Door*>* Doors, TArray<Enemy*>* Enemies, Zombie* zombie);
    Room(TArray<AnimatedSprite*>* WallSprites, TArray<Door*>* Doors, TArray<Enemy*>* Enemies, Boss* boss);
    ~Room();

    void Tick(float fElapsedTime);
    void Draw(float fElapsedTime);

private:
    TArray<AnimatedSprite*>* WallSprites;
    TArray<Door*>* Doors;
    TArray<Enemy*>* Enemies;
    Zombie* zombie = nullptr;
    Boss* boss = nullptr;
};
#endif