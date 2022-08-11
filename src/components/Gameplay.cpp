/******************************************************************************
**
** File      Gameplay.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include <iostream>
#include "Gameplay.h"

namespace zuma
{

Gameplay::Gameplay(sf::Vector2u size)
{
    m_gun.setPos({size.x / 2.0f, size.y / 2.0f});
}

void Gameplay::Draw(sf::RenderWindow *window)
{
    m_gun.Draw(window);
}

}