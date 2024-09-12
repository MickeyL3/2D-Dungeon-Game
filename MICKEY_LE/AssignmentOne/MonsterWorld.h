#pragma once

#ifndef MONSTERWORLD_H
#define MONSTERWORLD_H
#include "olcPixelGameEngine.h"
#include "Enemy.h"
#include "Door.h"
#include "Player.h"
#include "Boss.h"
#include "Zombie.h"
#include <vector>
#include <memory>
#include "AnimatedSprite.h"
#include "TArray.h"
#include "Actor.h"
#include "infoBar.h"
#include "TextRender.h"
#include "Room.h"

constexpr int SCREEN_WIDTH = 240;
constexpr int SCREEN_HEIGHT = 240;
constexpr int NOTIFICATION_BAR_HEIGHT = 32;
constexpr int PIXEL_SIZE = 4;
constexpr int ENEMY_COUNT = 3;
constexpr int TOTAL_ELEMENTS = 8;
constexpr int TILE_WIDTH = 12;
constexpr int TILE_HEIGHT = 12;
constexpr int ENEMY_HEALTH = 140;
constexpr int ENEMY_DAMAGE = 10;
constexpr int MAX_PLAYER_HEALTH = 200;
constexpr int HEALTH_POTION = 100;
constexpr int PLAYER_START_POS_X = 12;
constexpr int PLAYER_START_POS_Y = SCREEN_HEIGHT / 2;
constexpr int PLAYER_START_HEALTH = 200;
constexpr int PLAYER_DAMAGE = 20;
constexpr int ZOMBIE_POS_X = 50;
constexpr int ZOMBIE_POS_Y = 50;
constexpr int ZOMBIE_DAMAGE = 20;
constexpr int ZOMBIE_HEALTH = 200;
constexpr int BOSS_HEALTH = 300;
constexpr int BOSS_DAMAGE = 35;
constexpr int BOSS_POS_X = SCREEN_WIDTH - 80;
constexpr int BOSS_POS_Y = SCREEN_HEIGHT - 120;
constexpr int ENEMY_POS_X[] = { 50, 120 , 220 };
constexpr int ENEMY_POS_Y[] = { 120, 80, 165 };


class Enemy;
class Room;

class MonsterWorld : public olc::PixelGameEngine
{
public:
    MonsterWorld();
    ~MonsterWorld();
    virtual bool OnUserCreate() override;
    virtual bool OnUserUpdate(float fElapsedTime) override;
    void CheckCollisions();
    static MonsterWorld* Monster;
    bool CheckCollision(const Player& player, const Actor& actor) const;
    bool CheckIsLose();
    enum GameState
    {
        START_SCREEN,
        GAME_RUNNING,
        END_SCREEN
    };
private:
    int EnemyCounter = 0;
    int ZombieCounter = 0;
    int BossCounter = 0;
    int LoopPacing = 250;
    void InitializeDoors();
    void InitializeRooms();
    void InitializeRoomWalls();
    void DrawRoom();

    TArray<Enemy*> Enemies;
    TArray<Door*> R1Doors;
    TArray<Door*> R2Doors;
    TArray<AnimatedSprite*> BrickSprites;
    TArray<AnimatedSprite*> StoneSprites;

    Player* player = nullptr;
    Boss* boss = nullptr;
    Zombie* zombie = nullptr;
    InfoBar* infobar = nullptr;
    olc::Sprite* TilesetSprite = nullptr;
    AnimatedSprite* LockedDoorSprite = nullptr;
    AnimatedSprite* UnlockedDoorSprite = nullptr;
    Room* room1 = nullptr;
    Room* room2 = nullptr;
    Room* CurrentRoom = nullptr;

    olc::HWButton space;

    static const TVector2D<int> LeftWall;
    static const TVector2D<int> RightWall;
    static const TVector2D<int> TopWall;
    static const TVector2D<int> BottomWall;
    
    std::vector<std::vector<int>> RoomLayout;

    bool PickupPotion = false;
    bool PickupKey = false;
    bool allEnemiesDead = false;
    GameState currentState = START_SCREEN;
};
#endif // MONSTERWORLD_H