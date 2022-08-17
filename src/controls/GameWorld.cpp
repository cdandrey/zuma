/******************************************************************************
**
** File      GameWorld.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "GameWorld.h"
#include "GameState.h"

#include <iostream>

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
    const auto mode = sf::VideoMode::getDesktopMode();
    const auto windowSize = sf::Vector2u{mode.width,mode.height};
    m_windowUPtr = std::make_unique<sf::RenderWindow>(mode,"Zuma");
    m_windowUPtr->setFramerateLimit(60);
    m_gameStateUPtr = std::make_unique<GameState>();
    m_sceneMainMenuUptr = std::make_unique<SceneMainMenu>(windowSize);
    m_sceneGameplayUptr = std::make_unique<SceneGameplay>(windowSize);
    m_sceneScoreUptr = std::make_unique<SceneScore>(windowSize);
}

void GameWorld::destroy()
{
    m_windowUPtr->close();
}

bool GameWorld::isOpen() const 
{
    return m_windowUPtr->isOpen();
}

void GameWorld::input(const sf::Event &event)
{
    if (event.type == sf::Event::Closed)
    {
        destroy();
    }

    if (event.type == sf::Event::Resized) {
        m_windowUPtr->setView(sf::View{{0.0f, 0.0f,
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height)}});

        resize(m_windowUPtr->getSize());
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

void GameWorld::resize(sf::Vector2u windowSize)
{
    m_sceneMainMenuUptr->resize(windowSize);
    m_sceneGameplayUptr->resize(windowSize);
    m_sceneScoreUptr->resize(windowSize);
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