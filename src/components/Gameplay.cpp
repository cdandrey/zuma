/******************************************************************************
**
** File      Gameplay.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include <iostream>
#include "Gameplay.h"
#include "adapters/AdapterRotable.h"
#include "commands/CommandRotable.h"

namespace zuma
{

Gameplay::Gameplay(sf::Vector2u size)
{
    m_gun = std::make_shared<Gun>(sf::Vector2f{size.x / 2.0f, size.y / 2.0f});
}

void Gameplay::update()
{
    auto adapter = std::make_shared<AdapterRotable>(m_gun);
    auto cmd = std::make_shared<CommandRotable>(adapter);
    cmd->execute();
}

void Gameplay::rotateGun(sf::Vector2f position)
{
    m_gun->setProperty(RotatePositionProperty::key,position);
}

void Gameplay::draw(sf::RenderWindow *window)
{
    m_gun->draw(window);
}

}