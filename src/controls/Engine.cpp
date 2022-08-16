/******************************************************************************
**
** File      Engine.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Engine.h"
#include "GameWorld.h"
#include "GameState.h"

namespace zuma 
{

void Engine::exec()
{
    auto scene = std::make_unique<GameWorld>();
    auto handler = scene->getGameState()->getHandlerOfState();

    while (handler->isOpen(scene.get()))
    {
        handler->input(scene.get());
        handler->update(scene.get());
        handler->render(scene.get());

        if (scene->getGameState()->isChanged()) {
            handler = scene->getGameState()->getHandlerOfState();
        }
    }
}

}