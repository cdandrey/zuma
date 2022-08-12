/******************************************************************************
**
** File      CommandRotable.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "CommandRotable.h"

#include <cmath>
#include <iostream>

namespace zuma {

constexpr float coef_180_div_pi = 180.0f / 3.14f;

CommandRotable::CommandRotable(const AbstractAdapterRotablePtr& rotable)
    : m_rotable{ rotable }
{
}

Result<void> CommandRotable::execute()
{
    const auto onGetRotatePosition = [this](const PositionProperty::type& position) -> Result<void> {
        const auto onSetDirection = [this, &position](const RotatePositionProperty::type& rotatePosition) -> Result<void> {
            const auto dy = rotatePosition.y - position.y;
            const auto dx = rotatePosition.x - position.x;
            auto angel = std::atanf(dy / dx) * coef_180_div_pi;
            if (dx < 0 && dy > 0) {
                angel += 180;
            } else if (dx < 0 && dy < 0) {
                angel -= 180;
            }
            std::cout << dx << ", " << dy << ", " << angel << std::endl;
            return m_rotable->setDirection(angel);
        };
        return m_rotable->getRotatePosition().and_then(onSetDirection);
    };
    return m_rotable->getPosition().and_then(onGetRotatePosition);
}

}  // namespace zuma