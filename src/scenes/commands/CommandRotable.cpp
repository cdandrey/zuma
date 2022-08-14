/******************************************************************************
**
** File      CommandRotable.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "CommandRotable.h"

#include <cmath>

namespace zuma {

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
            auto angel = std::atanf(dy / dx) * AbstractCommand::cRadiansToGradusCoef;
            if (dx < 0 && dy > 0) {
                angel += 180;
            } else if (dx < 0 && dy < 0) {
                angel -= 180;
            }
            return m_rotable->setDirection(angel);
        };
        return m_rotable->getRotatePosition().and_then(onSetDirection);
    };
    return m_rotable->getPosition().and_then(onGetRotatePosition);
}

}  // namespace zuma