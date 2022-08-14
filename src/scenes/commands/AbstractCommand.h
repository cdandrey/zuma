/******************************************************************************
**
** File      AbstractCommand.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../../types/ExceptionError.h"

namespace zuma {

class AbstractCommand
{
public:
	AbstractCommand() = default;
	virtual ~AbstractCommand() = default;

	virtual Result<void> execute(float elapsedTime) = 0;
};

}  // namespace zuma