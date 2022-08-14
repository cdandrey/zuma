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

    bool isOpen(GameWorld *scene) const override;
    void Input(GameWorld *scene) override;
    void Update(GameWorld *scene) override;
    void Render(GameWorld *scene) override;
};

}