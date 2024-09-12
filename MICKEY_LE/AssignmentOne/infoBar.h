#pragma once
#ifndef INFOBAR_H
#define INFOBAR_H

#include "olcPixelGameEngine.h"
#include "AnimatedSprite.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <memory>
#include "TextRender.h"

class InfoBar 
{
public:
	InfoBar();
	void DrawPlayerHealth(olc::PixelGameEngine* pge, int health, olc::Sprite* tileset);
	void DrawPlayerPick(olc::PixelGameEngine* pge, const std::string& keyText, olc::vi2d playerPos, olc::Sprite* tileset);
	void DrawEnemyHealth(olc::PixelGameEngine* pge, int health, olc::vi2d enemyPos, olc::Sprite* tileset);
private:
	olc::Sprite* TilesetSprite;
};
#endif //INFOBAR_H

