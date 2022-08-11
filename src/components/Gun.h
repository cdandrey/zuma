/******************************************************************************
**
** File      Gun.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>

namespace zuma
{

class Gun
{
public:
    Gun();
    ~Gun() = default;

    void setSize(sf::Vector2f size);
    void setPos(sf::Vector2f pos);
    void setColor(sf::Color color);
    void setRotate(float angel);

    void Draw(sf::RenderWindow *window);

private:
   sf::Texture m_texture;
   sf::Sprite m_sprite; 
};

}