/******************************************************************************
**
** File      Scene.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <memory>

#include "../components/Gameplay.h"
#include "../components/MainMenu.h"

namespace sf {
class RenderWindow;
}

namespace zuma 
{

class GameState;

class Scene
{
public:
    Scene();
    ~Scene();

    bool isOpen() const;
    void Input();
    void Update();
    void Render();

    sf::RenderWindow* getWindow() const;
    GameState* getGameState() const;
    MainMenu* getMainMenu() const;
    Gameplay* getGameplay() const;

private:
    std::unique_ptr<sf::RenderWindow> m_windowUPtr;
    std::unique_ptr<GameState> m_gameStateUPtr;
    std::unique_ptr<MainMenu> m_mainMenuUPtr;
    std::unique_ptr<Gameplay> m_gameplayUPtr;

    void Create();
    void Destroy();
};

}
