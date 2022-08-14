/******************************************************************************
**
** File      HandlerSceneScore.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractHandlerScene.h"

namespace zuma {

class HandlerSceneScore : public AbstractHandlerScene
{
public:
    HandlerSceneScore() = default;
    ~HandlerSceneScore() = default;

    bool isOpen(GameScenes *scene) const override;
    void Input(GameScenes *scene) override;
    void Update(GameScenes *scene) override;
    void Render(GameScenes *scene) override;
};

}