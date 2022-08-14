/******************************************************************************
**
** File      SceneScore.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "components/Button.h"

namespace zuma
{

class SceneScore
{
public:
    explicit SceneScore(sf::Vector2u windowSize);
    ~SceneScore() = default;

    void Draw(sf::RenderWindow *window) const;

    bool ButtonOkMouseClick(sf::Vector2i mousePos);
    void ButtonOkMouseHover(sf::Vector2i mousePos);

private:
    Button m_buttonOk;
    sf::RectangleShape m_rectBox;
};

} // namespace zuma