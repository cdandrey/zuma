/******************************************************************************
**
** File      Score.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "Button.h"

namespace zuma
{

class Score
{
public:
    explicit Score(sf::Vector2u windowSize);
    ~Score() = default;

    void Draw(sf::RenderWindow *window) const;

    bool ButtonOkMouseClick(sf::Vector2i mousePos);
    void ButtonOkMouseHover(sf::Vector2i mousePos);

private:
    Button m_buttonOk;
    sf::RectangleShape m_rectBox;
};

} // namespace zuma