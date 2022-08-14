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

Result<void> CommandCircleMovable::execute()
{
    const auto onGetPosition = [this](const PositionProperty::type& position) -> Result<void> {
        const auto onGetOrigin = [this, &position](const OriginProperty::type& origin) -> Result<void> {
            const auto onSetPosition = [this, &position, &origin](const CircleVelocityProperty::type& circleVelocity) -> Result<void> {
                const auto cy = origin.y - position.y;
                const auto cx = position.x - origin.x;
                auto ca = std::atanf(cx / cy) * AbstractCommand::cRadiansToGradusCoef;
                ca += circleVelocity;
                if (cy < 0) {
                    ca += 180;
                }
                ca /= AbstractCommand::cRadiansToGradusCoef;
                const auto r = std::sqrtf(cy*cy + cx*cx);
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