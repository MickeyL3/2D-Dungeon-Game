#include "Player.h"
#include "AnimatedSprite.h"
#include "MonsterWorld.h"


Player::Player(const TVector2D<int>& position, int health, int damage)
    : Character(position, health, damage), AttackSprite(nullptr), DeadSprite(nullptr), sprite(nullptr)
{
    std::cout << "Player created" << std::endl;
    Position = position;
}

Player::~Player()
{
    std::cout << "Player destroyed" << std::endl;

}

void Player::SetSprite(AnimatedSprite* newSprite)
{
    sprite = newSprite;
}

void Player::SetAttackSprite(AnimatedSprite* newSprite)
{
    AttackSprite = newSprite;
}

void Player::SetDeadSprite(AnimatedSprite* newSprite)
{
    DeadSprite = newSprite;
}

void Player::Tick(float fElapsedTime)
{
    if (isDead()) 
    {
        PlayerMode = DIE;
        return;
    }

    olc::PixelGameEngine* pge = MonsterWorld::Monster;
    const float movementSpeed = 30000.0f;
   
    PlayerMode = IDLE;
    if (pge->GetKey(olc::Key::LEFT).bHeld) 
    {
        Position.X -= static_cast<int>(movementSpeed * fElapsedTime);
    }
    if (pge->GetKey(olc::Key::RIGHT).bHeld) 
    {
        Position.X += static_cast<int>(movementSpeed * fElapsedTime);
    }
    if (pge->GetKey(olc::Key::UP).bHeld) 
    {
        Position.Y -= static_cast<int>(movementSpeed * fElapsedTime);
    }
    if (pge->GetKey(olc::Key::DOWN).bHeld) 
    {
        Position.Y += static_cast<int>(movementSpeed * fElapsedTime);
    }
    if (pge->GetKey(olc::Key::SPACE).bHeld && PlayerMode != DIE)
    {
        PlayerMode = ATTACK;
    }

    const int screenWidth = SCREEN_WIDTH - 24;
    const int screenHeight = SCREEN_HEIGHT - 24;

    if (Position.X < 12) Position.X = 12;
    if (Position.X > screenWidth) Position.X = screenWidth;
    if (Position.Y < 12) Position.Y = 12;
    if (Position.Y > screenHeight) Position.Y = screenHeight;
  
}


void Player::Draw(float fElapsedTime)
{
    olc::vi2d olcPosition(Position.X, Position.Y);
    if (PlayerMode == IDLE) 
    {
        sprite->DrawAt(fElapsedTime, olcPosition);
    }
    else if (PlayerMode == ATTACK) 
    {
        AttackSprite->DrawAt(fElapsedTime, olcPosition);
    }
    else if (PlayerMode == DIE) 
    {
        DeadSprite->DrawAt(fElapsedTime, olcPosition);
    }
}

void Player::TakeDamage(int damage, InfoBar* infobar, olc::PixelGameEngine* pge, olc::Sprite* tileset)
{
    if (Health - damage <= 0)
    {
        Health = 0;
    }
    else
    {
        Health -= damage;
    }
    
    std::cout << "Player takes damage! Health is now: " << Health << std::endl;

    infobar->DrawPlayerHealth(pge, Health, tileset);
}

void Player::Move(const TVector2D<int>& direction)
{
    Position += direction;
}

bool Player::isDead() const
{
    return Health <= 0;
}

void Player::Attack(Enemy* enemy, InfoBar* infobar, olc::PixelGameEngine* pge, olc::Sprite* tileset)
{
    
    if (enemy)
    {
        std::cout << "Player attacks! Enemy health before: " << enemy->GetHealth() << std::endl;
        PlayerMode = ATTACK;

        enemy->TakeDamage(Damage);
        std::cout << "Enemy health after: " << enemy->GetHealth() << std::endl;

        olc::vi2d enemyPos = olc::vi2d(enemy->GetPosition().X, enemy->GetPosition().Y);
        infobar->DrawEnemyHealth(pge, enemy->GetHealth(), enemyPos, tileset);
    }
    if (enemy->IsDead())
    {
        std::cout << "Enemy defeated!" << std::endl;
    }
 
    Zombie* zombie = dynamic_cast<Zombie*>(enemy);

    if (zombie)
    {
        std::cout << "Player attacks Zombie! Zombie health before: " << zombie->GetHealth() << std::endl;
        PlayerMode = ATTACK;

        zombie->TakeDamage(Damage);
        std::cout << "Zombie health after: " << zombie->GetHealth() << std::endl;
        olc::vi2d zombiePos = olc::vi2d(zombie->GetPosition().X, zombie->GetPosition().Y);
        infobar->DrawEnemyHealth(pge, zombie->GetHealth(), zombiePos, tileset);

        if (zombie->IsDead())
        {
            std::cout << "Zombie defeated!" << std::endl;
            
        }
        else
        {
            std::cout << "Zombie still alive!" << std::endl;
        }
    }

    Boss* boss = dynamic_cast<Boss*>(enemy);

    if (boss)
    {
        std::cout << "Player attacks Boss! Boss health before: " << boss->GetHealth() << std::endl;
        PlayerMode = ATTACK;

        boss->TakeDamage(Damage);
        std::cout << "Boss health after: " << boss->GetHealth() << std::endl;
        olc::vi2d bossPos = olc::vi2d(boss->GetPosition().X, boss->GetPosition().Y);
        infobar->DrawEnemyHealth(pge, boss->GetHealth(), bossPos, tileset);

        if (boss->IsDead())
        {
            std::cout << "Boss defeated!" << std::endl;

        }
        else
        {
            std::cout << "Boss still alive!" << std::endl;
        }
    } 
}

void Player::IncreaseHealth(int amount)
{
    if ((Health + amount) > MAX_PLAYER_HEALTH)
    {
        Health = MAX_PLAYER_HEALTH;
    }
    else 
    {
        Health += amount;
    }
}


Player::mode_t Player::GetPlayerMode() const
{
    return PlayerMode;
}

