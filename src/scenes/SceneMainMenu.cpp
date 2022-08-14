/******************************************************************************
**
** File      SceneMainMenu.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "SceneMainMenu.h"
#include "../configs/Config.h"

namespace zuma
{

SceneMainMenu::SceneMainMenu(sf::Vector2u windowSize)
    : m_buttonPlay{config::menu::button::size(windowSize),config::menu::button::position(2,0,windowSize),"Play"}
    , m_buttonExit{config::menu::button::size(windowSize),config::menu::button::position(2,1,windowSize),"Exit"}
{
}

void SceneMainMenu::Draw(sf::RenderWindow *window) const
{
    m_buttonPlay.Draw(window);
    m_buttonExit.Draw(window);
}

bool SceneMainMenu::ButtonPlayMouseClick(sf::Vector2i mousePos)
{
    return m_buttonPlay.isHover(mousePos);
}

bool SceneMainMenu::ButtonExitMouseClick(sf::Vector2i mousePos)
{
    return m_buttonExit.isHover(mousePos);
}

void SceneMainMenu::ButtonPlayMouseHover(sf::Vector2i mousePos)
{
    m_buttonPlay.unhovered();

    if (m_buttonPlay.isHover(mousePos)) {
        m_buttonPlay.hovered();
    };
}

void SceneMainMenu::ButtonExitMouseHover(sf::Vector2i mousePos)
{
    m_buttonExit.unhovered();

    if (m_buttonExit.isHover(mousePos)) {
        m_buttonExit.hovered();
    };
}

}
