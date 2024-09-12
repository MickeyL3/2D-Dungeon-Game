#pragma once
#ifndef TEXT_RENDER_H
#define TEXT_RENDER_H

#include "olcPixelGameEngine.h"
#include <memory>

class TextRenderer
{
public:
    static olc::vi2d GetCharTilePos(char c);
    static void RenderText(olc::PixelGameEngine* pge, const std::string& text, olc::Sprite* tileset, olc::vi2d pos);
};
#endif // !TEXT_RENDER_H
