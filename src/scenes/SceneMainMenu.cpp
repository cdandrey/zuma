/******************************************************************************
**
** File      SceneMainMenu.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "SceneMainMenu.h"

namespace zuma
{

SceneMainMenu::SceneMainMenu(sf::Vector2u windowSize)
{
    resize(windowSize);

    m_buttonPlay.setText("Play");
    m_buttonPlay.setStyle(config::menu::button::cStyle);

    m_buttonExit.setText("Exit");
    m_buttonExit.setStyle(config::menu::button::cStyle);
}

void SceneMainMenu::resize(sf::Vector2u windowSize)
{
    using namespace config::menu;

    m_windowSize = windowSize;

    m_buttonPlay.setSize(config::scaled(m_windowSize,button::cBaseSize));
    m_buttonPlay.setPosition(config::scaled(m_windowSize,button::position(2,0,m_windowSize)));

    m_buttonExit.setSize(config::scaled(m_windowSize,button::cBaseSize));
    m_buttonExit.setPosition(config::scaled(m_windowSize,button::position(2,1,m_windowSize)));
}

void SceneMainMenu::draw(sf::RenderWindow *window) const
{
    m_buttonPlay.draw(window);
    m_buttonExit.draw(window);
}

bool SceneMainMenu::buttonPlayMouseClick(sf::Vector2i mousePos)
{
    return m_buttonPlay.isHover(mousePos);
}

bool SceneMainMenu::buttonExitMouseClick(sf::Vector2i mousePos)
{
    return m_buttonExit.isHover(mousePos);
}

void SceneMainMenu::buttonPlayMouseHover(sf::Vector2i mousePos)
{
    m_buttonPlay.unhovered();

    if (m_buttonPlay.isHover(mousePos)) {
        m_buttonPlay.hovered();
    };
}

void SceneMainMenu::buttonExitMouseHover(sf::Vector2i mousePos)
{
    m_buttonExit.unhovered();

    if (m_buttonExit.isHover(mousePos)) {
        m_buttonExit.hovered();
    };
}

}   // namespace zuma
