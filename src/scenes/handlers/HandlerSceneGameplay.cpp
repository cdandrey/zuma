/******************************************************************************
**
** File      HandlerSceneGameplay.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "HandlerSceneGameplay.h"
#include "../../controls/GameWorld.h"
#include "../../controls/GameState.h"

namespace zuma {

bool HandlerSceneGameplay::isOpen(GameWorld *scene) const
{
    return scene->isOpen();
}

void HandlerSceneGameplay::Input(GameWorld *scene) 
{
    sf::Event event;
    while (scene->getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            scene->getWindow()->close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            scene->getGameState()->changed(GameState::State::Menu);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            scene->getGameState()->changed(GameState::State::Score);
        }
        if (event.type == sf::Event::MouseMoved) {
            const auto mousePos = sf::Mouse::getPosition(*scene->getWindow());
            scene->getSceneGameplay()->rotateGun(static_cast<sf::Vector2f>(mousePos));
        }
    }

}

void HandlerSceneGameplay::Update(GameWorld *scene)
{
    scene->Update();
    scene->getSceneGameplay()->update();
    scene->getSceneGameplay()->draw(scene->getWindow());
}

void HandlerSceneGameplay::Render(GameWorld *scene)
{
    scene->Render();
}

}