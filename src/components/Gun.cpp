/******************************************************************************
**
** File      Gun.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Gun.h"

namespace zuma
{

Gun::Gun()
{
    m_texture.loadFromFile("resources/img/gun.png");
    m_sprite.setTexture(m_texture);
}

void Gun::setPos(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}

void Gun::setColor(sf::Color color)
{
    m_sprite.setColor(color);
}

void Gun::setRotate(float angel)
{
    m_sprite.setRotation(angel);
}

void Gun::Draw(sf::RenderWindow *window)
{
    window->draw(m_sprite);
}

}