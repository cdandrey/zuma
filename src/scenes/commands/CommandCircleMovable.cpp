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
                const auto safeAtan = [this](float x, float y) -> float {
                    return y != 0.0f ? std::atanf(x / y) * AbstractCommand::cRadiansToGradusCoef
                                     : 90.0f;
                };
                auto ca = safeAtan(cx,cy);
                ca += circleVelocity;
                ca /= AbstractCommand::cRadiansToGradusCoef;
                const auto r = std::sqrtf(cx*cx + cy*cy);
                const auto dy = std::cosf(ca) * r;
                const auto dx = std::sinf(ca) * r;
                if (cy < 0) {
                    return m_movable->setPosition(PositionProperty::type{origin.x - dx, origin.y + dy});
                }
                return m_movable->setPosition(PositionProperty::type{origin.x + dx, origin.y - dy});
            };
            return m_movable->getCircleVelocity().and_then(onSetPosition);
        };
        return m_movable->getOrigin().and_then(onGetOrigin);
    };
    return m_movable->getPosition().and_then(onGetPosition);
}

}  // namespace zuma