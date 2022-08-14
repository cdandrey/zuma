/******************************************************************************
**
** File      Engine.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Engine.h"
#include "GameScenes.h"
#include "GameState.h"

namespace zuma 
{

void Engine::exec()
{
    auto scene = std::make_unique<GameScenes>();
    auto handler = scene->getGameState()->getHandlerOfState();

    while (handler->isOpen(scene.get()))
    {
        handler->Input(scene.get());
        handler->Update(scene.get());
        handler->Render(scene.get());

        if (scene->getGameState()->isChanged()) {
            handler = scene->getGameState()->getHandlerOfState();
        }
    }
}

}