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

    bool isOpen(Scene *scene) const override;
    void Input(Scene *scene) override;
    void Update(Scene *scene) override;
    void Render(Scene *scene) override;
};

}