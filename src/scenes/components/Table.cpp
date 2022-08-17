/******************************************************************************
**
** File      Table.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Table.h"

#include <iostream>

namespace zuma
{

Table::Table(size_t rowCount, size_t colCount)
    : m_cells{rowCount,std::vector<sf::Text>{colCount,sf::Text{}}}
{
}

void Table::setSize(sf::Vector2f size)
{
    m_rect.setSize(size);
    m_rect.setOrigin(size / 2.0f);   // center of rect
}

void Table::setPosition(sf::Vector2f position)
{
    m_rect.setPosition(position);
    const float cellWidth = m_cells.size() > 0 ? m_rect.getSize().x / m_cells.begin()->size()
                                               : m_rect.getSize().x;
    const float cellHeight = m_cells.size() > 0 ? m_rect.getSize().y / m_cells.size()
                                                : m_rect.getSize().y;
    
    const float left = position.x - m_rect.getSize().x / 2.0f + /*padding*/ m_rect.getSize().x / 14.0f;
    const float top  = position.y - m_rect.getSize().y / 2.0f + /*padding*/ m_rect.getSize().y / 12.0f;


    for (size_t row = 0; row < m_cells.size(); ++row) {
        for (size_t col = 0; col < m_cells.begin()->size(); ++col) {
            m_cells[row][col].setPosition({left + col*cellWidth, top + row*cellHeight});
        }
    }
}

void Table::setText(size_t row, size_t col, const std::string &text)
{
    if (m_cells.size() == 0 || row >= m_cells.size() || col >= m_cells.begin()->size()) {
        return;
    }

    m_cells[row][col].setString(text);
}

void Table::setStyle(const config::table::Style &style)
{
    m_rect.setFillColor(style.cFillColor);
    m_rect.setOutlineColor(style.cBorderColor);
    m_rect.setOutlineThickness(style.cBorderThickness);

    m_font.loadFromFile(style.cFontPath);

    for (auto &row : m_cells) {
        for (auto &cell : row) {
            cell.setFont(m_font);
            cell.setCharacterSize(style.cTextSize);
            cell.setFillColor(style.cTextColor);
        }
    }
}


void Table::draw(sf::RenderWindow *window) const
{
    window->draw(m_rect);

    for (const auto &row : m_cells) {
        for (const auto &cell : row) {
            window->draw(cell);
        }
    }
}

}   // namespace zuma