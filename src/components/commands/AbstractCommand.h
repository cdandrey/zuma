/******************************************************************************
**
** File      AbstractCommand.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../../types/ExceptionError.h"
#include <memory>

namespace zuma {

class AbstractCommand
{
public:
	AbstractCommand() = default;
	virtual ~AbstractCommand() = default;

	virtual Result<void> execute() = 0;
};

using AbstractCommandPtr = std::shared_ptr<AbstractCommand>;

}  // namespace zuma