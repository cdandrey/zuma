/******************************************************************************
**
** File      CommandMovable.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "CommandMovable.h"

#include <cmath>

namespace zuma {

CommandMovable::CommandMovable(const AbstractAdapterMovablePtr& movable)
    : m_movable{ movable }
{
}

Result<void> CommandMovable::execute(float elapsedTime)
{
    const auto onGetDirection = [this, elapsedTime](const PositionProperty::type& position) -> Result<void> {
        const auto onGetVelocity = [this, elapsedTime, position](const DirectionProperty::type& direction) -> Result<void> {
            const auto onSetPosition = [this, elapsedTime, position, direction] (const VelocityProperty::type& velocity) -> Result<void> {
                const auto x = position.x + std::cosf(direction) * velocity * elapsedTime; 
                const auto y = position.y + std::sinf(direction) * velocity * elapsedTime; 
                return m_movable->setPosition({x, y});
            };
            return m_movable->getVelocity().and_then(onSetPosition); 
        };
        return m_movable->getDirection().and_then(onGetVelocity);
    };
    return m_movable->getPosition().and_then(onGetDirection);
}

}  // namespace zuma