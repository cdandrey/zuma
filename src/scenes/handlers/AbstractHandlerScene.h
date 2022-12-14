/******************************************************************************
**
** File      AbstractHandlerScene.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <memory>

namespace zuma {

class GameWorld;

class AbstractHandlerScene
{
public:

    virtual ~AbstractHandlerScene() = default;

    virtual bool isOpen(GameWorld *scene) const = 0;
    virtual void input(GameWorld *scene) = 0;
    virtual void update(GameWorld *scene) = 0;
    virtual void render(GameWorld *scene) = 0;
};

using AbstractHandlerSceneUPtr = std::unique_ptr<AbstractHandlerScene>;

}