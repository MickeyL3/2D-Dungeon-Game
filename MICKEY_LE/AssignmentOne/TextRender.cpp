#include "TextRender.h"

olc::vi2d TextRenderer::GetCharTilePos(char c)
{
    int baseASCII_A = (int)'A'; 
    int baseASCII_0 = (int)'0'; 

    int tileWidth = 14;  
    int charTilesPerRow = 20;  
    int alphaTilesPerRow = 5;

    if (c >= 'A' && c <= 'T')
    {
        int charIndex = c - baseASCII_A;
        int tileX = (charIndex * 13) + 1;
        int tileY = 573;
        return olc::vi2d(tileX, tileY);
    }
    
    else if (c >= 'U' && c <= 'Z')
    {
        int charIndex = c - 'U';
        int tileX = (charIndex * 13) + 1;
        int tileY = 586;
        return olc::vi2d(tileX, tileY);
    }

    else if (c == '0')
    {
        return olc::vi2d(313, 586);
    }

    else if (c >= '1' && c <= '5')
    {
        int charIndex = c - '1';
        int tileX = (charIndex * 13) + 261;
        int tileY = 573;
        return olc::vi2d(tileX, tileY);
    }

    else if (c >= '6' && c <= '9')
    {
        int charIndex = c - '6';
        int tileX = (charIndex * 13) + 261;
        int tileY = 586;
        return olc::vi2d(tileX, tileY);
    }

    else if (c == ' ')
    {
        return olc::vi2d(1, 560);
    }

    return olc::vi2d(638, 638);
}

void TextRenderer::RenderText(olc::PixelGameEngine* pge, const std::string& text, olc::Sprite* tileset, olc::vi2d pos)
{
    int tileSize = 12; 
    for (size_t Idx = 0; Idx < text.size(); ++Idx)
    {
        char c = text[Idx];
        olc::vi2d tilePos = GetCharTilePos(c);
        pge->DrawPartialSprite(pos.x + Idx * tileSize, pos.y, tileset, tilePos.x, tilePos.y, tileSize, tileSize);
    }
}
