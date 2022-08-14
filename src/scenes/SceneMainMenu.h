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

    void Draw(sf::RenderWindow *window) const;

    bool ButtonPlayMouseClick(sf::Vector2i mousePos);
    bool ButtonExitMouseClick(sf::Vector2i mousePos);
    void ButtonPlayMouseHover(sf::Vector2i mousePos);
    void ButtonExitMouseHover(sf::Vector2i mousePos);

private:
    Button m_buttonPlay;
    Button m_buttonExit;
};

}