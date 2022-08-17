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
{
    using namespace config::score;

    resize(windowSize);

    m_buttonOk.setText("OK");
    m_buttonOk.setStyle(config::menu::button::cStyle);

    m_rectBox.setFillColor(box::cFillColor);
    m_rectBox.setOutlineThickness(box::cBorderThickness);
    m_rectBox.setOutlineColor(box::cBorderColor);

    m_font.loadFromFile(config::menu::button::cStyle.cFontPath);

    m_shotsTitle.setString("Count shots: ");
    configText(&m_shotsTitle);

    m_shotsValue.setString("0");
    configText(&m_shotsValue);

    m_destroedTitle.setString("Balls destroyed: ");
    configText(&m_destroedTitle);

    m_destroedValue.setString("0");
    configText(&m_destroedValue);

    m_efficiencyTitle.setString("Shot efficiency: ");
    configText(&m_efficiencyTitle);

    m_efficiencyValue.setString("0");
    configText(&m_efficiencyValue);
}

void SceneScore::draw(sf::RenderWindow *window) const
{
    window->draw(m_rectBox);
    window->draw(m_shotsTitle);
    window->draw(m_shotsValue);
    window->draw(m_destroedTitle);
    window->draw(m_destroedValue);
    window->draw(m_efficiencyTitle);
    window->draw(m_efficiencyValue);
    m_buttonOk.draw(window);
}

void SceneScore::resize(sf::Vector2u windowSize)
{
    using namespace config::score;

    m_windowSize = windowSize;

    m_buttonOk.setSize(config::scaled(m_windowSize,button::cBaseSize));
    m_buttonOk.setPosition(config::scaled(m_windowSize,button::cBasePosition));

    m_rectBox.setSize(config::scaled(m_windowSize,box::cBaseSize));
    m_rectBox.setOrigin(m_rectBox.getSize() / 2.0f);
    m_rectBox.setPosition(config::scaled(m_windowSize,box::cBasePosition));

    m_shotsTitle.setPosition(config::scaled(m_windowSize,text::cBasePosition));
    m_shotsValue.setPosition(text::shiftLeft(m_windowSize,m_shotsTitle.getPosition()).x, m_shotsTitle.getPosition().y);
    m_destroedTitle.setPosition(m_shotsTitle.getPosition().x, text::shiftDown(m_windowSize,m_shotsTitle.getPosition()).y);
    m_destroedValue.setPosition(text::shiftLeft(m_windowSize,m_destroedTitle.getPosition()).x, m_destroedTitle.getPosition().y);
    m_efficiencyTitle.setPosition(m_shotsTitle.getPosition().x,text::shiftDown(m_windowSize,m_destroedTitle.getPosition()).y);
    m_efficiencyValue.setPosition(text::shiftLeft(m_windowSize,m_efficiencyTitle.getPosition()).x, m_efficiencyTitle.getPosition().y);
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

void SceneScore::configText(sf::Text *text)
{
    text->setFont(m_font);
    text->setCharacterSize(config::menu::button::cStyle.cTextSize);
    text->setFillColor(config::menu::button::cStyle.cTextColor);
}

void SceneScore::setScore(const config::gamestate::DataScore &data) 
{
    m_shotsValue.setString(std::to_string(data.shots));
    m_destroedValue.setString(std::to_string(data.destroed));
    m_efficiencyValue.setString(std::to_string(data.efficiency));
}

}   // namespace zuma
