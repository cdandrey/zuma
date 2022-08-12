/******************************************************************************
**
** File      HandlerSceneMenu.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "AbstractHandlerScene.h"

namespace zuma {

class HandlerSceneMenu : public AbstractHandlerScene
{
public:
    HandlerSceneMenu() = default;
    ~HandlerSceneMenu() = default;

    bool isOpen(Scene *scene) const override;
    void Input(Scene *scene) override;
    void Update(Scene *scene) override;
    void Render(Scene *scene) override;
};

}