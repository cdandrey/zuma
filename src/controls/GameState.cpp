/******************************************************************************
**
** File      GameState.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/
#include <iostream>

#include "GameState.h"
#include "../scenes/handlers/HandlerSceneMenu.h"
#include "../scenes/handlers/HandlerSceneGameplay.h"
#include "../scenes/handlers/HandlerSceneScore.h"

namespace zuma
{

GameState::GameState()
    : m_state{State::Menu}
{
}

AbstractHandlerSceneUPtr GameState::getHandlerOfState()
{
    m_handlerOfState = m_state;

    switch (m_state)
    {
    case State::Menu:
    case State::Pause: 
        return std::make_unique<HandlerSceneMenu>(); 
    case State::Play:

        return std::make_unique<HandlerSceneGameplay>(); 
    case State::Score:
        return std::make_unique<HandlerSceneScore>(); 
    }
}

void GameState::changed(State state)
{
    m_state = state;
    std::cout << "Chaged state: " << static_cast<int>(m_state) << std::endl;
}

bool GameState::isChanged() const
{
    return m_state != m_handlerOfState;
}

}