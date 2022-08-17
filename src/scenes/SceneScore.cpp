/******************************************************************************
**
** File      SceneScore.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "SceneScore.h"

namespace zuma
{

SceneScore::SceneScore(sf::Vector2u windowSize)
    : m_table{4,2}
{
    resize(windowSize);

    m_buttonOk.setText("OK");
    m_buttonOk.setStyle(config::menu::button::cStyle);

    m_table.setStyle(config::score::cStyle);

    m_table.setText(0, 0, "Count shots: ");
    m_table.setText(0, 1, "0");
    m_table.setText(1, 0, "Balls destroyed: ");
    m_table.setText(1, 1, "0");
    m_table.setText(2, 0, "Shot efficiency: ");
    m_table.setText(2, 1, "0");
}

void SceneScore::draw(sf::RenderWindow *window) const
{
    m_table.draw(window);
    m_buttonOk.draw(window);
}

void SceneScore::resize(sf::Vector2u windowSize)
{
    using namespace config::score;

    m_windowSize = windowSize;

    m_buttonOk.setSize(config::scaled(m_windowSize,button::cBaseSize));
    m_buttonOk.setPosition(config::scaled(m_windowSize,button::cBasePosition));

    m_table.setSize(config::scaled(m_windowSize,cBaseSize));
    m_table.setPosition(config::scaled(m_windowSize,cBasePosition));
}

bool SceneScore::buttonOkMouseClick(sf::Vector2i mousePos)
{
    return m_buttonOk.isHover(mousePos);
}

void SceneScore::buttonOkMouseHover(sf::Vector2i mousePos)
{
    m_buttonOk.unhovered();

    if (m_buttonOk.isHover(mousePos)) {
        m_buttonOk.hovered();
    };
}

void SceneScore::setScore(const config::gamestate::DataScore &data) 
{
    m_table.setText(0,1,std::to_string(data.shots));
    m_table.setText(1,1,std::to_string(data.destroed));
    m_table.setText(2,1,std::to_string(data.efficiency));
}

}   // namespace zuma
