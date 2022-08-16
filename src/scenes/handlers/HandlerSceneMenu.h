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
    void input(GameWorld *scene) override;
    void update(GameWorld *scene) override;
    void render(GameWorld *scene) override;
};

}