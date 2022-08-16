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
    void input(GameWorld *scene) override;
    void update(GameWorld *scene) override;
    void render(GameWorld *scene) override;
};

}