/******************************************************************************
**
** File      GameScenes.h
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

class GameScenes
{
public:
    GameScenes();
    ~GameScenes();

    bool isOpen() const;
    void Input();
    void Update();
    void Render();

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

    void Create();
    void Destroy();
};

}
