/******************************************************************************
**
** File      Gun.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractObject.h"
#include <SFML/Graphics.hpp>

namespace zuma
{

class Gun : public AbstractObject
{
public:
    explicit Gun(sf::Vector2f position);
    ~Gun() = default;

    void setColor(sf::Color color);

    void draw(sf::RenderWindow *window);

private:
   sf::Texture m_texture;
   sf::Sprite m_sprite; 
};

}