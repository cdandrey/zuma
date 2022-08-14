/******************************************************************************
**
** File      CommandCircleMovable.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractCommand.h"
#include "../adapters/AdapterMovable.h"

namespace zuma {

class CommandCircleMovable : public AbstractCommand
{
public:
    explicit CommandCircleMovable(const AbstractAdapterMovablePtr& rotable);

    Result<void> execute(float elapsedTime) override;

private:
    AbstractAdapterMovablePtr m_movable;
};

}  // namespace zuma
