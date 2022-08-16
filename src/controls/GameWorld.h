/******************************************************************************
**
** File      GameWorld.h
** Author    Andrii Sydorenko
**
******************************************************************************/

#pragma once

#include <memory>

#include "../scenes/SceneGameplay.h"
#include "../scenes/SceneMainMenu.h"
#include "../scenes/SceneScore.h"

namespace sf {
class RenderWindow;
}

namespace zuma 
{

class GameState;

class GameWorld
{
public:
    GameWorld();
    ~GameWorld();

    bool isOpen() const;
    void input();
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
};

}
