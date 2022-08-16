/******************************************************************************
**
** File      GameState.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../scenes/handlers/AbstractHandlerScene.h"
#include "../configs/Config.h"

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
    void setScore(const config::gamestate::DataScore& data);
    config::gamestate::DataScore getScore() const;
    AbstractHandlerSceneUPtr getHandlerOfState();

private:
    State m_state;
    State m_handlerOfState;
    config::gamestate::DataScore m_data;
};

}