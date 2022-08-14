/******************************************************************************
**
** File      CommandRotable.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractCommand.h"
#include "../adapters/AdapterRotable.h"

namespace zuma {

class CommandRotable : public AbstractCommand
{
public:
    explicit CommandRotable(const AbstractAdapterRotablePtr& rotable);

    Result<void> execute(float elapsedTime) override;

private:
    AbstractAdapterRotablePtr m_rotable;
};

}  // namespace zuma
