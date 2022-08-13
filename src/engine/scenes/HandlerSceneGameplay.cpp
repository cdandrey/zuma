#include "HandlerSceneGameplay.h"
#include "Scene.h"
#include "../GameState.h"

#include <iostream>

namespace zuma {

bool HandlerSceneGameplay::isOpen(Scene *scene) const
{
    return scene->isOpen();
}

void HandlerSceneGameplay::Input(Scene *scene) 
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
            //std::cout << mousePos.x << ", " << mousePos.y << std::endl;
            scene->getGameplay()->rotateGun(static_cast<sf::Vector2f>(mousePos));
        }
    }

}

void HandlerSceneGameplay::Update(Scene *scene)
{
    scene->Update();
    scene->getGameplay()->update();
    scene->getGameplay()->draw(scene->getWindow());
}

void HandlerSceneGameplay::Render(Scene *scene)
{
    scene->Render();
}

}