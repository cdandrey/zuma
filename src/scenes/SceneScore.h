/******************************************************************************
**
** File      SceneScore.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "components/Button.h"
#include "../configs/Config.h"

namespace zuma
{

class SceneScore
{
public:
    explicit SceneScore(sf::Vector2u windowSize);
    ~SceneScore() = default;

    void draw(sf::RenderWindow *window) const;
    void resize(sf::Vector2u windowSize);

    bool buttonOkMouseClick(sf::Vector2i mousePos);
    void buttonOkMouseHover(sf::Vector2i mousePos);

    void setScore(const config::gamestate::DataScore &data);

private:
    sf::Vector2u m_windowSize;

    Button m_buttonOk;
    sf::RectangleShape m_rectBox;
   
    // TO DO: components score
    sf::Text m_shotsTitle;
    sf::Text m_shotsValue;

    sf::Text m_destroedTitle;
    sf::Text m_destroedValue;

    sf::Text m_efficiencyTitle;
    sf::Text m_efficiencyValue;

    sf::Font m_font;

    void configText(sf::Text *text);
};

} // namespace zuma