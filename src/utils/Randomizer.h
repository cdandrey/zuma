/******************************************************************************
**
** File      Randomizer.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <random>
#include <SFML/Graphics.hpp>

namespace zuma
{

class RandomizeColor
{
public:
    RandomizeColor();
    ~RandomizeColor() = default;

    sf::Color getRandomColor();

private:
    std::random_device m_dev;
    std::mt19937 m_mt19937;
    std::uniform_int_distribution<std::mt19937::result_type> m_dist;

    inline static const std::vector<sf::Color> cColors = {
            sf::Color::Yellow,
            sf::Color::Cyan,
            sf::Color::Magenta,
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color{230, 130, 0, 255} // orange
        };
};

}   // namespace zuma