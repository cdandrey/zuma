/******************************************************************************
**
** File      GameWorld.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include "../scenes/SceneGameplay.h"
#include "../scenes/SceneMainMenu.h"
#include "../scenes/SceneScore.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace zuma 
{

class GameState;

class GameWorld
{
public:
    GameWorld();
    ~GameWorld();

    bool isOpen() const;
    void input(const sf::Event &event);
    void update();
    void render();

    sf::RenderWindow* getWindow() const;
    GameState* getGameState() const;
    SceneMainMenu* getSceneMainMenu() const;
    SceneGameplay* getSceneGameplay() const;
    SceneScore* getSceneScore() const;

private:
    std::unique_ptr<GameState> m_gameStateUPtr;
    std::unique_ptr<sf::RenderWindow> m_windowUPtr;
    std::unique_ptr<SceneMainMenu> m_sceneMainMenuUptr;
    std::unique_ptr<SceneGameplay> m_sceneGameplayUptr;
    std::unique_ptr<SceneScore> m_sceneScoreUptr;

    void create();
    void destroy();
    void resize(sf::Vector2u windowSize);
};

}
