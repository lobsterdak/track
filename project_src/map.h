#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Map
{
public:
    static const int Height_map = 25;
    static const int Width_map = 40;
    Image map_image;
    
    Texture tex_map;
    Sprite s_map;
    void draw(RenderWindow* window)
    {
        map_image.loadFromFile("map.png");
        tex_map.loadFromImage(map_image);
        s_map.setTexture(tex_map);
        for (int i = 0; i < Height_map; i++)
            for (int j = 0; j < Width_map; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
                if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
                s_map.setPosition(j * 32, i * 32);
                window->draw(s_map);
            }
    }
    sf::String TileMap[Height_map] = {
        "0000000000000000000000000000000000000000",
        "0                                      0",
        "0   sss sss                            0",
        "0   s   s                              0",
        "0   sss sss                            0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0000000000000000000000000000000000000000",
    };
};




