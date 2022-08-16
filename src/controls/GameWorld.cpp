/******************************************************************************
**
** File      GameWorld.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "GameWorld.h"
#include "GameState.h"

#include <SFML/Graphics.hpp>


namespace zuma
{

GameWorld::GameWorld()
{
    create();
}

GameWorld::~GameWorld()
{
    destroy();
}

void GameWorld::create() 
{
    m_windowUPtr = std::make_unique<sf::RenderWindow>(sf::VideoMode{1920,1080},"Zuma");
    m_gameStateUPtr = std::make_unique<GameState>();
    m_sceneMainMenuUptr = std::make_unique<SceneMainMenu>(sf::Vector2u{1920,1080});
    m_sceneGameplayUptr = std::make_unique<SceneGameplay>(sf::Vector2u{1920,1080});
    m_sceneScoreUptr = std::make_unique<SceneScore>(sf::Vector2u{1920,1080});
}

void GameWorld::destroy()
{
    m_windowUPtr->close();
}

bool GameWorld::isOpen() const 
{
    return m_windowUPtr->isOpen();
}

void GameWorld::input()
{
    sf::Event event;
    while (m_windowUPtr->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            destroy();
        }
    }
}

void GameWorld::update()
{
    m_windowUPtr->clear(sf::Color::White);
}

void GameWorld::render() 
{
    m_windowUPtr->display();
}

sf::RenderWindow *GameWorld::getWindow() const
{
    return m_windowUPtr.get();
}

GameState *GameWorld::getGameState() const 
{
    return m_gameStateUPtr.get();
}

SceneMainMenu* GameWorld::getSceneMainMenu() const
{
    return m_sceneMainMenuUptr.get();
}

SceneGameplay *GameWorld::getSceneGameplay() const
{
    return m_sceneGameplayUptr.get();
}

SceneScore *GameWorld::getSceneScore() const
{
    return m_sceneScoreUptr.get();
}

}