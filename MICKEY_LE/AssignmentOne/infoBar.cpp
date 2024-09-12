#include "infoBar.h"

InfoBar::InfoBar()
    : TilesetSprite(nullptr)
{
   
}

void InfoBar::DrawPlayerHealth(olc::PixelGameEngine* pge, int health, olc::Sprite* tileset)
{
    std::string healthText = "PLAYER HEALTH " + std::to_string(health);
    olc::vi2d pos(24, 252); 
    TextRenderer::RenderText(pge, healthText, tileset, pos);
}

void InfoBar::DrawPlayerPick(olc::PixelGameEngine* pge, const std::string& keyText, olc::vi2d playerPos, olc::Sprite* tileset)
{
    olc::vi2d pos = playerPos + olc::vi2d(-12,-24);
    TextRenderer::RenderText(pge, keyText, tileset, pos);
}

void InfoBar::DrawEnemyHealth(olc::PixelGameEngine* pge, int health, olc::vi2d enemyPos, olc::Sprite* tileset)
{
    std::string healthText = std::to_string(health);
    olc::vi2d pos = enemyPos + olc::vi2d(0, -24); 
    TextRenderer::RenderText(pge, healthText, tileset, pos);
}

