/******************************************************************************
**
** File      ObjectGun.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractObject.h"
#include <SFML/Graphics.hpp>

namespace zuma
{

class ObjectGun : public AbstractObject
{
public:
    explicit ObjectGun(sf::Vector2u windowSize);
    ~ObjectGun() = default;

    void updateGraphics();
    void draw(sf::RenderWindow *window);

private:
   sf::Texture m_texture;
   sf::Sprite m_sprite; 
};

}