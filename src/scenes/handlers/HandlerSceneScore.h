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
    void Input(GameWorld *scene) override;
    void Update(GameWorld *scene) override;
    void Render(GameWorld *scene) override;
};

}