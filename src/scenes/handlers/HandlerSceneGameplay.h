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

    bool isOpen(GameScenes *scene) const override;
    void Input(GameScenes *scene) override;
    void Update(GameScenes *scene) override;
    void Render(GameScenes *scene) override;
};

}