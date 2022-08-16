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
    : m_buttonOk{config::score::size(windowSize,config::score::button::cBaseSize),
                 config::score::position(windowSize,config::score::button::cBasePosition),
                 "OK"}
{
    using namespace config::score;

    m_rectBox.setSize(size(windowSize,box::cBaseSize));
    m_rectBox.setOrigin(config::origin(m_rectBox.getSize()));
    m_rectBox.setPosition(position(windowSize,config::score::box::cBasePosition));
    m_rectBox.setFillColor(box::cFillColor);
    m_rectBox.setOutlineThickness(box::cBorderThickness);
    m_rectBox.setOutlineColor(box::cBorderColor);

    m_font.loadFromFile(config::button::cFontPath);

    m_shotsTitle.setPosition(position(windowSize,text::cBasePosition));
    m_shotsTitle.setString("Count shots: ");
    configText(&m_shotsTitle);

    m_shotsValue.setPosition(text::shiftLeft(windowSize,m_shotsTitle.getPosition()).x, m_shotsTitle.getPosition().y);
    m_shotsValue.setString("0");
    configText(&m_shotsValue);

    m_destroedTitle.setPosition(m_shotsTitle.getPosition().x, text::shiftDown(windowSize,m_shotsTitle.getPosition()).y);
    m_destroedTitle.setString("Balls destroyed: ");
    configText(&m_destroedTitle);

    m_destroedValue.setPosition(text::shiftLeft(windowSize,m_destroedTitle.getPosition()).x, m_destroedTitle.getPosition().y);
    m_destroedValue.setString("0");
    configText(&m_destroedValue);

    m_efficiencyTitle.setPosition(m_shotsTitle.getPosition().x,text::shiftDown(windowSize,m_destroedTitle.getPosition()).y);
    m_efficiencyTitle.setString("Shot efficiency: ");
    configText(&m_efficiencyTitle);

    m_efficiencyValue.setPosition(text::shiftLeft(windowSize,m_efficiencyTitle.getPosition()).x, m_efficiencyTitle.getPosition().y);
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
    m_buttonOk.Draw(window);
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
    text->setCharacterSize(config::button::cTextSize);
    text->setFillColor(config::button::cTextColor);
    const auto textRect = text->getLocalBounds();
    text->setOrigin(textRect.left, textRect.top);
}

void SceneScore::setScore(const config::gamestate::DataScore &data) 
{
    m_shotsValue.setString(std::to_string(data.shots));
    m_destroedValue.setString(std::to_string(data.destroed));
    m_efficiencyValue.setString(std::to_string(data.efficiency));
}

}   // namespace zuma
