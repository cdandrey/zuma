/******************************************************************************
**
** File      GameScenes.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "GameScenes.h"
#include "GameState.h"

#include <SFML/Graphics.hpp>


namespace zuma
{

GameScenes::GameScenes()
{
    Create();
}

GameScenes::~GameScenes()
{
    Destroy();
}

void GameScenes::Create() 
{
    m_windowUPtr = std::make_unique<sf::RenderWindow>(sf::VideoMode{1920,1080},"Zuma");
    m_gameStateUPtr = std::make_unique<GameState>();
    m_sceneMainMenuUptr = std::make_unique<SceneMainMenu>(sf::Vector2u{1920,1080});
    m_sceneGameplayUptr = std::make_unique<SceneGameplay>(sf::Vector2u{1920,1080});
    m_sceneScoreUptr = std::make_unique<SceneScore>(sf::Vector2u{1920,1080});
}

void GameScenes::Destroy()
{
    m_windowUPtr->close();
}

bool GameScenes::isOpen() const 
{
    return m_windowUPtr->isOpen();
}

void GameScenes::Input()
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

void GameScenes::Update()
{
    m_windowUPtr->clear(sf::Color::White);
}

void GameScenes::Render() 
{
    m_windowUPtr->display();
}

sf::RenderWindow *GameScenes::getWindow() const
{
    return m_windowUPtr.get();
}

GameState *GameScenes::getGameState() const 
{
    return m_gameStateUPtr.get();
}

SceneMainMenu* GameScenes::getSceneMainMenu() const
{
    return m_sceneMainMenuUptr.get();
}

SceneGameplay *GameScenes::getSceneGameplay() const
{
    return m_sceneGameplayUptr.get();
}

SceneScore *GameScenes::getSceneScore() const
{
    return m_sceneScoreUptr.get();
}

}