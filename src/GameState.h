/******************************************************************************
**
** File      GameState.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "scenes/AbstractHandlerScene.h"

namespace zuma
{

class GameState
{
public:
    GameState();
    ~GameState() = default;

    enum class State {
        Menu,
        Pause,
        Play,
        Score
    };

    void changed(State state);
    bool isChanged() const;
    AbstractHandlerSceneUPtr getHandlerOfState();

private:
    State m_state;
    State m_handlerOfState;
};

}