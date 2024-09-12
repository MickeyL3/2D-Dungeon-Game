#include "MonsterWorld.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

MonsterWorld* MonsterWorld::Monster = nullptr;
const TVector2D<int> MonsterWorld::LeftWall = { 0, SCREEN_HEIGHT/2 };
const TVector2D<int> MonsterWorld::RightWall = { SCREEN_WIDTH - 24, SCREEN_HEIGHT / 2 };
const TVector2D<int> MonsterWorld::TopWall = { SCREEN_WIDTH / 2, 0 };
const TVector2D<int> MonsterWorld::BottomWall = { SCREEN_WIDTH / 2, SCREEN_HEIGHT - 12 };

MonsterWorld::MonsterWorld()
{
    MonsterWorld::Monster = this;    
}

MonsterWorld::~MonsterWorld()
{
    Monster = nullptr;
    TilesetSprite = nullptr;
    player = nullptr;
    boss = nullptr;
    zombie = nullptr;
    infobar = nullptr;
    LockedDoorSprite = nullptr;
    UnlockedDoorSprite = nullptr;
    room1 = nullptr;
    room2 = nullptr;
    CurrentRoom = nullptr;
}

bool MonsterWorld::OnUserCreate()
{
    std::cout << "Initializing MonsterWorld..." << std::endl;
    TilesetSprite = new olc::Sprite("tileset.png");
    
    if (!TilesetSprite || TilesetSprite->width <= 0 || TilesetSprite->height <= 0)
    {
        std::cerr << "Failed to load tileset.png" << std::endl;
        return false;
    }
    std::cout << "TilesetSprite loaded successfully. Width: " << TilesetSprite->width
        << ", Height: " << TilesetSprite->height << std::endl;

    // Initialize enemy sprite 
    FAnimSequence EnemySequence = { olc::vi2d(339,66), olc::vi2d(12,12),3,1.0f };
    FAnimSequence DeadEnemySequence = { olc::vi2d(365,144), olc::vi2d(12,12),1,1.0f };
    AnimatedSprite* animStill = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, EnemySequence);
    AnimatedSprite* animLoopOnce = new AnimatedSprite(TilesetSprite, EAnimationType::LOOP_ONCE, DeadEnemySequence);
    AnimatedSprite* animLoopForever = new AnimatedSprite(TilesetSprite, EAnimationType::LOOP_FOREVER, EnemySequence);

    for (int Idx = 0; Idx < ENEMY_COUNT; Idx++)
    {
        Enemy* EnemyN = new Enemy(TVector2D<int>(ENEMY_POS_X[Idx], ENEMY_POS_Y[Idx]), ENEMY_HEALTH, ENEMY_DAMAGE);
        EnemyN->SetSprite(animLoopForever);
        EnemyN->SetDeadSprite(animLoopOnce);
        EnemyN->SetPosition(TVector2D<int>(ENEMY_POS_X[Idx], ENEMY_POS_Y[Idx]));
        Enemies.AddElement(EnemyN);
    }
    
    // Initialize player sprite and create player object
    FAnimSequence playerSequence = { olc::vi2d(1,131), olc::vi2d(12,12),1,1.0f };
    FAnimSequence playerAttackSequence = { olc::vi2d(456,14), olc::vi2d(12,12),1,1.0f };
    FAnimSequence playerDeadSequence = { olc::vi2d(300,160), olc::vi2d(12,12),1,1.0f };
    AnimatedSprite* playerDeadSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, playerDeadSequence);
    AnimatedSprite* playerAttackSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, playerAttackSequence);
    AnimatedSprite* playerSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, playerSequence);
    player = new Player(TVector2D<int>(PLAYER_START_POS_X, PLAYER_START_POS_Y), PLAYER_START_HEALTH, PLAYER_DAMAGE);
    player->SetSprite(playerSprite);
    player->SetAttackSprite(playerAttackSprite);
    player->SetDeadSprite(playerDeadSprite);

    //Initialize zombie sprite
    FAnimSequence ZombieSequence = { olc::vi2d(638,105), olc::vi2d(12,24),1,1.0f };
    FAnimSequence ZombieDeadSequence = { olc::vi2d(378,248), olc::vi2d(12,12),1,1.0f };
    AnimatedSprite* zombieSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, ZombieSequence);
    AnimatedSprite* deadZombieSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, ZombieDeadSequence);
    zombie = new Zombie(TVector2D < int>(ZOMBIE_POS_X, ZOMBIE_POS_Y), ZOMBIE_HEALTH, ZOMBIE_DAMAGE);
    zombie->SetSprite(zombieSprite);
    zombie->SetDeadSprite(deadZombieSprite);

    // Initialize boss sprite
    FAnimSequence bossSequence = { olc::vi2d(586,1), olc::vi2d(24,24),1,1.0f };
    FAnimSequence bossDeadSequence = { olc::vi2d(1,456), olc::vi2d(12,12),1,1.0f };
    AnimatedSprite* bossSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, bossSequence);
    AnimatedSprite* deadBossSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, bossDeadSequence);
    boss = new Boss(TVector2D<int>(BOSS_POS_X,BOSS_POS_Y), BOSS_HEALTH, BOSS_DAMAGE);
    boss->SetSprite(bossSprite);
    boss->SetDeadSprite(deadBossSprite);
    
    InitializeRooms();
    InitializeDoors();
      
    return true;
}

bool MonsterWorld::OnUserUpdate(float fElapsedTime)
{
    if (player == nullptr) 
    {
        std::cout << "player is null ptr" << std::endl;
        return false;
    }
    
    switch (currentState)
    {
        case START_SCREEN:
        {
            TextRenderer::RenderText(this, "PRESS ENTER TO START THE GAME", TilesetSprite, olc::vi2d(0, SCREEN_HEIGHT/2));
            if ((this->GetKey(olc::Key::ENTER).bPressed))
            {
                currentState = GAME_RUNNING;
            } 
            break;
        }
        case GAME_RUNNING:
        {
            if (LoopPacing >= 250)
            {
                Clear(olc::BLACK);
                CurrentRoom->Tick(fElapsedTime);
                CurrentRoom->Draw(fElapsedTime);
                player->Tick(fElapsedTime);
                player->Draw(fElapsedTime);
                
                if (Enemies.GetElement(0)->IsDead() && Enemies.GetElement(1)->IsDead()
                    && Enemies.GetElement(2)->IsDead() && (CurrentRoom == room2))
                {
                    allEnemiesDead = true;
                    boss->Tick(fElapsedTime);
                    boss->Draw(fElapsedTime);
                }
                CheckCollisions();
                LoopPacing = 0;
            }
            LoopPacing++;

            if (PickupKey && CheckCollision(*player, *R2Doors.GetElement(1)))
            {
                currentState = END_SCREEN;
            }

            infobar->DrawPlayerHealth(this, player->GetHealth(), TilesetSprite);

            

            if (CheckIsLose())
            {
                TextRenderer::RenderText(this, "GAME OVER", TilesetSprite, olc::vi2d(66, 100));
            }
            break;
        }
        case END_SCREEN:
        {
            TextRenderer::RenderText(this, "CONGRATS YOU WIN", TilesetSprite, olc::vi2d(15, 140));
            break;
        }
        
    }
    return true;
}


void MonsterWorld::CheckCollisions()
{
    /* Enemy collision checks */
    for (int Idx = 0; Idx < ENEMY_COUNT; ++Idx)
    {
        Enemy* CurrentEnemy = Enemies.GetElement(Idx);
        if (!CurrentEnemy->IsDead() && CheckCollision(*player, *CurrentEnemy))
        {
            if (player->GetPlayerMode() == Player::ATTACK)
            {
                player->Attack(CurrentEnemy, infobar, this, TilesetSprite);
                olc::vi2d enemyPos = olc::vi2d(CurrentEnemy->GetPosition().X, CurrentEnemy->GetPosition().Y);
                infobar->DrawEnemyHealth(this, CurrentEnemy->GetHealth(), enemyPos, TilesetSprite);                
            }
            else
            {
                EnemyCounter++;
            }
        }
        if (EnemyCounter >= 5)
        {
            std::cout << "Enemy attacks Player" << player->GetHealth() << std::endl;
            player->TakeDamage(CurrentEnemy->GetDamage(), infobar, this, TilesetSprite);
            std::cout << "Player health after: " << player->GetHealth() << std::endl;
            EnemyCounter = 0;        
        }  
    }

    /* Zombie collision checks */
    if (!zombie->IsDead() && CheckCollision(*player, *zombie))
    { 
        if (player->GetPlayerMode() == Player::ATTACK)
        {
            player->Attack(zombie, infobar, this, TilesetSprite);
            olc::vi2d zombiePos = olc::vi2d(zombie->GetPosition().X, zombie->GetPosition().Y);
            infobar->DrawEnemyHealth(this, zombie->GetHealth(), zombiePos, TilesetSprite);
        }
        else
        {
            ZombieCounter++;
        }
    }
    if (ZombieCounter >= 5)
    {

        std::cout << "Zombie attacks Player!" << player->GetHealth() << std::endl;
        player->TakeDamage(zombie->GetDamage(), infobar, this, TilesetSprite);
        std::cout << "Player health after: " << player->GetHealth() << std::endl;
        ZombieCounter = 0;

    }
    if (zombie->IsDead() && CheckCollision(*player, *zombie) && !PickupPotion)
    {
        player->IncreaseHealth(HEALTH_POTION);
        std::cout << "Player health after: " << player->GetHealth() << std::endl;
        PickupPotion = true;
        FAnimSequence RemoveSequence = { olc::vi2d(170,92), olc::vi2d(12,12),1,1.0f };
        AnimatedSprite* removeSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, RemoveSequence);
        zombie->SetDeadSprite(removeSprite);
        std::string text = "UP HEALTH";
        olc::vi2d playerPos = olc::vi2d(player->GetPosition().X, player->GetPosition().Y);
        infobar->DrawPlayerPick(this, text, playerPos, TilesetSprite);
    }

    /* Boss collision Checks */
    if (!boss->IsDead() && allEnemiesDead && CheckCollision(*player, *boss))
    {
        if (player->GetPlayerMode() == Player::ATTACK)
        {
            player->Attack(boss, infobar, this, TilesetSprite);
            olc::vi2d bossPos = olc::vi2d(boss->GetPosition().X, boss->GetPosition().Y);
            infobar->DrawEnemyHealth(this, boss->GetHealth(), bossPos, TilesetSprite);

        }
        else
        {
            BossCounter++;
        }
    }
    if (BossCounter >= 5)
    {
        std::cout << "Boss attacks Player!" << player->GetHealth() << std::endl;
        player->TakeDamage(boss->GetDamage(), infobar, this, TilesetSprite);
        std::cout << "Player health after: " << player->GetHealth() << std::endl;
        BossCounter = 0;
    }

    /* Check for cleared enemies to open door to room 2*/
    if (zombie->IsDead() && Enemies.GetElement(0)->IsDead() &&
        Enemies.GetElement(1)->IsDead() && Enemies.GetElement(2)->IsDead() &&
        (CurrentRoom == room1))
    {
        R1Doors.GetElement(1)->Unlock();
    }

    /* Switch to room2, and reset the enemies and zombie*/
    if (zombie->IsDead() && Enemies.GetElement(0)->IsDead() &&
        Enemies.GetElement(1)->IsDead() && Enemies.GetElement(2)->IsDead() &&
        (CurrentRoom == room1) && CheckCollision(*player, *R1Doors.GetElement(1)))
    {
        CurrentRoom = room2;
        Enemies.GetElement(0)->Reset(ENEMY_HEALTH);
        Enemies.GetElement(1)->Reset(ENEMY_HEALTH);
        Enemies.GetElement(2)->Reset(ENEMY_HEALTH);
    }

    /* Key to unlock room 2 door collision check */
    if (boss->IsDead() && zombie->IsDead() && CheckCollision(*player, *boss) && !PickupKey && (CurrentRoom == room2))
    {
        PickupKey = true;
        FAnimSequence RemoveSequence = { olc::vi2d(170,92), olc::vi2d(12,12),1,1.0f };
        AnimatedSprite* removeSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, RemoveSequence);
        boss->SetDeadSprite(removeSprite);
        std::string text = "DOOR OPENED";
        olc::vi2d playerPos = olc::vi2d(player->GetPosition().X, player->GetPosition().Y);
        infobar->DrawPlayerPick(this, text, playerPos, TilesetSprite);
        R2Doors.GetElement(1)->Unlock();
    }

}

bool MonsterWorld::CheckCollision(const Player& player, const Actor& actor) const
{
    return
        (player.GetPosition().X < actor.GetPosition().X + 12 &&
        player.GetPosition().X + 12 > actor.GetPosition().X &&
        player.GetPosition().Y < actor.GetPosition().Y + 12 &&
        player.GetPosition().Y + 12 > actor.GetPosition().Y);
}

bool MonsterWorld::CheckIsLose()
{
    return player->GetHealth() <= 0;
}

void MonsterWorld::InitializeDoors()
{
    Door* start = new Door(LockedDoorSprite, UnlockedDoorSprite, false);
    start->SetPosition(LeftWall);
    R1Doors.AddElement(start);
    Door* toR2 = new Door(LockedDoorSprite, UnlockedDoorSprite, true);
    toR2->SetPosition(RightWall);
    R1Doors.AddElement(toR2);

    Door* fromR1 = new Door(LockedDoorSprite, UnlockedDoorSprite, true);
    fromR1->SetPosition(LeftWall);
    R2Doors.AddElement(fromR1);
    Door* end = new Door(LockedDoorSprite, UnlockedDoorSprite, true);
    end->SetPosition(RightWall);
    R2Doors.AddElement(end);
}

void MonsterWorld::InitializeRooms()
{
    // Create animated door sprites
    FAnimSequence lockedDoorSequence = { olc::vi2d(66, 14), olc::vi2d(12, 12), 1, 0.0f };
    FAnimSequence unlockedDoorSequence = { olc::vi2d(144, 14), olc::vi2d(12, 12), 1, 0.0f };
    LockedDoorSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, lockedDoorSequence);
    UnlockedDoorSprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, unlockedDoorSequence);

    // Initialize RoomLayout with bricks
    FAnimSequence brick1 = { olc::vi2d(1, 1), olc::vi2d(12, 12), 1, 0.0f };
    FAnimSequence brick2 = { olc::vi2d(14, 1), olc::vi2d(12, 12), 1, 0.0f };
    FAnimSequence brick3 = { olc::vi2d(66, 1), olc::vi2d(12, 12), 1, 0.0f };
    FAnimSequence brick4 = { olc::vi2d(105, 1), olc::vi2d(12, 12), 1, 0.0f };
    AnimatedSprite* brick1Sprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, brick1);
    AnimatedSprite* brick2Sprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, brick2);
    AnimatedSprite* brick3Sprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, brick3);
    AnimatedSprite* brick4Sprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, brick4);
    BrickSprites.AddElement(brick1Sprite);
    BrickSprites.AddElement(brick2Sprite);
    BrickSprites.AddElement(brick3Sprite);
    BrickSprites.AddElement(brick4Sprite);

    // Initialize RoomLayout with bricks
    FAnimSequence stone1 = { olc::vi2d(1, 40), olc::vi2d(12, 12), 1, 0.0f };
    FAnimSequence stone2 = { olc::vi2d(14, 40), olc::vi2d(12, 12), 1, 0.0f };
    FAnimSequence stone3 = { olc::vi2d(66, 40), olc::vi2d(12, 12), 1, 0.0f };
    AnimatedSprite* stone1Sprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, stone1);
    AnimatedSprite* stone2Sprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, stone2);
    AnimatedSprite* stone3Sprite = new AnimatedSprite(TilesetSprite, EAnimationType::STILL, stone3);
    StoneSprites.AddElement(stone1Sprite);
    StoneSprites.AddElement(stone2Sprite);
    StoneSprites.AddElement(stone3Sprite);

    room1 = new Room(&BrickSprites, &R1Doors, &Enemies, zombie);
    room2 = new Room(&StoneSprites, &R2Doors, &Enemies, boss);
    CurrentRoom = room1;
}


