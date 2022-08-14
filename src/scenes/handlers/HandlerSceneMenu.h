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

    bool isOpen(GameWorld *scene) const override;
    void Input(GameWorld *scene) override;
    void Update(GameWorld *scene) override;
    void Render(GameWorld *scene) override;
};

}