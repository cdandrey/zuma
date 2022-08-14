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

    bool isOpen(GameScenes *scene) const override;
    void Input(GameScenes *scene) override;
    void Update(GameScenes *scene) override;
    void Render(GameScenes *scene) override;
};

}