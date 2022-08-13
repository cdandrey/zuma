/******************************************************************************
**
** File      Scene.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "Scene.h"
#include "../GameState.h"

#include <SFML/Graphics.hpp>


namespace zuma
{

Scene::Scene()
{
    Create();
}

Scene::~Scene()
{
    Destroy();
}

void Scene::Create() 
{
    m_windowUPtr = std::make_unique<sf::RenderWindow>(sf::VideoMode{1920,1080},"Zuma");
    m_gameStateUPtr = std::make_unique<GameState>();
    m_mainMenuUPtr = std::make_unique<MainMenu>(sf::Vector2u{1920,1080});
    m_gameplayUPtr = std::make_unique<Gameplay>(sf::Vector2u{1920,1080});
    m_scoreUPtr = std::make_unique<Score>(sf::Vector2u{1920,1080});
}

void Scene::Destroy()
{
    m_windowUPtr->close();
}

bool Scene::isOpen() const 
{
    return m_windowUPtr->isOpen();
}

void Scene::Input()
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

void Scene::Update()
{
    m_windowUPtr->clear(sf::Color::White);
}

void Scene::Render() 
{
    m_windowUPtr->display();
}

sf::RenderWindow *Scene::getWindow() const
{
    return m_windowUPtr.get();
}

GameState *Scene::getGameState() const 
{
    return m_gameStateUPtr.get();
}

MainMenu* Scene::getMainMenu() const
{
    return m_mainMenuUPtr.get();
}

Gameplay *Scene::getGameplay() const
{
    return m_gameplayUPtr.get();
}

Score *Scene::getScore() const
{
    return m_scoreUPtr.get();
}

}