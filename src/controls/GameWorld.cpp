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
    Create();
}

GameWorld::~GameWorld()
{
    Destroy();
}

void GameWorld::Create() 
{
    m_windowUPtr = std::make_unique<sf::RenderWindow>(sf::VideoMode{1920,1080},"Zuma");
    m_gameStateUPtr = std::make_unique<GameState>();
    m_sceneMainMenuUptr = std::make_unique<SceneMainMenu>(sf::Vector2u{1920,1080});
    m_sceneGameplayUptr = std::make_unique<SceneGameplay>(sf::Vector2u{1920,1080});
    m_sceneScoreUptr = std::make_unique<SceneScore>(sf::Vector2u{1920,1080});
}

void GameWorld::Destroy()
{
    m_windowUPtr->close();
}

bool GameWorld::isOpen() const 
{
    return m_windowUPtr->isOpen();
}

void GameWorld::Input()
{
    sf::Event event;
    while (m_windowUPtr->pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
            event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            Destroy();
        }
    }
}

void GameWorld::Update()
{
    m_windowUPtr->clear(sf::Color::White);
}

void GameWorld::Render() 
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