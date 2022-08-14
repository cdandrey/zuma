/******************************************************************************
**
** File      AbstractHandlerScene.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <memory>

namespace zuma {

class GameScenes;

class AbstractHandlerScene
{
public:

    virtual ~AbstractHandlerScene() = default;

    virtual bool isOpen(GameScenes *scene) const = 0;
    virtual void Input(GameScenes *scene) = 0;
    virtual void Update(GameScenes *scene) = 0;
    virtual void Render(GameScenes *scene) = 0;
};

using AbstractHandlerSceneUPtr = std::unique_ptr<AbstractHandlerScene>;

}