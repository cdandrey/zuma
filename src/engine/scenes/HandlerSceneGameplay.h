/******************************************************************************
**
** File      HandlerSceneGameplay.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractHandlerScene.h"

namespace zuma {

class HandlerSceneGameplay : public AbstractHandlerScene
{
public:
    HandlerSceneGameplay() = default;
    ~HandlerSceneGameplay() = default;

    bool isOpen(Scene *scene) const override;
    void Input(Scene *scene) override;
    void Update(Scene *scene) override;
    void Render(Scene *scene) override;
};

}