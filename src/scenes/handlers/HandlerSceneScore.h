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

    bool isOpen(GameWorld *scene) const override;
    void input(GameWorld *scene) override;
    void update(GameWorld *scene) override;
    void render(GameWorld *scene) override;
};

}