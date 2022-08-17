/******************************************************************************
**
** File      Table.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../../configs/Config.h"
#include <SFML/Graphics.hpp>

namespace zuma
{

class Table
{
public:
    Table(size_t rowCount, size_t colCount);
    ~Table() = default;

    void draw(sf::RenderWindow *window) const;
    
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void setText(size_t row, size_t col, const std::string &text);
    void setStyle(const config::table::Style &style);

private:

    sf::RectangleShape m_rect;
    std::vector<std::vector<sf::Text>> m_cells;
    sf::Font m_font;
};

}