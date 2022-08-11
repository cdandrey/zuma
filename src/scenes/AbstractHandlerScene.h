/******************************************************************************
**
** File      AbstractHandlerScene.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <memory>

namespace zuma {

class Scene;

class AbstractHandlerScene
{
public:

    virtual ~AbstractHandlerScene() = default;

    virtual bool isOpen(Scene *scene) const = 0;
    virtual void Input(Scene *scene) = 0;
    virtual void Update(Scene *scene) = 0;
    virtual void Render(Scene *scene) = 0;
};

using AbstractHandlerSceneUPtr = std::unique_ptr<AbstractHandlerScene>;

}