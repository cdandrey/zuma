/******************************************************************************
**
** File      CommandCircleMovable.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "CommandCircleMovable.h"

#include <cmath>

namespace zuma {

CommandCircleMovable::CommandCircleMovable(const AbstractAdapterMovablePtr& movable)
    : m_movable{ movable }
{
}

Result<void> CommandCircleMovable::execute(float elapsedTime)
{
    const auto onGetPosition = [this,elapsedTime](const PositionProperty::type& position) -> Result<void> {
        const auto onGetOrigin = [this,elapsedTime,position](const OriginProperty::type& origin) -> Result<void> {
            const auto onSetPosition = [this, elapsedTime, position, origin](const CircleVelocityProperty::type& circleVelocity) -> Result<void> {
                const auto cy = origin.y - position.y;
                const auto cx = position.x - origin.x;
                auto ca = std::atan2f(cx,cy);
                ca += (circleVelocity * elapsedTime);
                const auto r = std::sqrtf(cx*cx + cy*cy);
                const auto dy = std::cosf(ca) * r;
                const auto dx = std::sinf(ca) * r;
                return m_movable->setPosition(PositionProperty::type{origin.x + dx, origin.y - dy});
            };
            return m_movable->getCircleVelocity().and_then(onSetPosition);
        };
        return m_movable->getOrigin().and_then(onGetOrigin);
    };
    return m_movable->getPosition().and_then(onGetPosition);
}

}  // namespace zuma