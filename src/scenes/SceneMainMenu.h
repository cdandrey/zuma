/******************************************************************************
**
** File      SceneMainMenu.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "components/Button.h"

namespace zuma
{

class SceneMainMenu
{
public:
    explicit SceneMainMenu(sf::Vector2u size);
    ~SceneMainMenu() = default;

    void draw(sf::RenderWindow *window) const;
    void resize(sf::Vector2u windowSize);

    bool buttonPlayMouseClick(sf::Vector2i mousePos);
    bool buttonExitMouseClick(sf::Vector2i mousePos);
    void buttonPlayMouseHover(sf::Vector2i mousePos);
    void buttonExitMouseHover(sf::Vector2i mousePos);

private:
    sf::Vector2u m_windowSize;
    Button m_buttonPlay;
    Button m_buttonExit;
};

}