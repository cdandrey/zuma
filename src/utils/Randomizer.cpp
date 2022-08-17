/******************************************************************************
**
** File      Randomizer.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Randomizer.h"

namespace zuma
{

RandomizeColor::RandomizeColor()
    : m_mt19937{std::seed_seq{m_dev(),m_dev(),m_dev(),m_dev()}}
    , m_dist{0,static_cast<unsigned>(cColors.size() - 1)}
{
}

sf::Color RandomizeColor::getRandomColor()
{
    return cColors[m_dist(m_mt19937)];
}

}   // namespace zuma