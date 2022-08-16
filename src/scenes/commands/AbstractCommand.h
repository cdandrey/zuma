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

	// TO DO: moved parameter to constructor with variadical template
	virtual Result<void> execute(float elapsedTime) = 0;
};

}  // namespace zuma