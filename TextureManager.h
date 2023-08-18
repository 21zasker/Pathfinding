#pragma once
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    sf::Texture icons_texture;
    sf::Texture no_icons_texture;
    sf::Texture cursor_texture;
    sf::Texture dungeon_texture;

    TextureManager()
    {
        icons_texture.loadFromFile("Assets/UI.png");
        no_icons_texture.loadFromFile("Assets/UI2.png");
        cursor_texture.loadFromFile("Assets/cursors.png");
        dungeon_texture.loadFromFile("Assets/tiles_1.png");
    }
};