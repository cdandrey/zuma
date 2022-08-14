/******************************************************************************
**
** File      CommandMovable.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractCommand.h"
#include "../adapters/AdapterMovable.h"

namespace zuma {

class CommandMovable : public AbstractCommand
{
public:
    explicit CommandMovable(const AbstractAdapterMovablePtr& rotable);

    Result<void> execute(float elapsedTime) override;

private:
    AbstractAdapterMovablePtr m_movable;
};

}  // namespace zuma
