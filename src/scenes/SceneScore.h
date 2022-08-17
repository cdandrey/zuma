/******************************************************************************
**
** File      SceneScore.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "components/Button.h"
#include "components/Table.h"

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
    Table m_table;
};

} // namespace zuma