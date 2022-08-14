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

Result<void> CommandRotable::execute(float /*elapsedTime*/)
{
    const auto onGetRotatePosition = [this](const PositionProperty::type& position) -> Result<void> {
        const auto onSetDirection = [this, position](const RotatePositionProperty::type& rotatePosition) -> Result<void> {
            const auto dy = rotatePosition.y - position.y;
            const auto dx = rotatePosition.x - position.x;
            const auto angel = std::atan2f(dy, dx);
            return m_rotable->setDirection(angel);
        };
        return m_rotable->getRotatePosition().and_then(onSetDirection);
    };
    return m_rotable->getPosition().and_then(onGetRotatePosition);
}

}  // namespace zuma