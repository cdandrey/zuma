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

void HandlerSceneGameplay::input(GameWorld *scene) 
{
    sf::Event event;
    while (scene->getWindow()->pollEvent(event)) {

        scene->input(event);

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            scene->getGameState()->changed(GameState::State::Menu);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            scene->getSceneGameplay()->gameStop();
            scene->getGameState()->changed(GameState::State::Score);
            scene->getGameState()->setScore(scene->getSceneGameplay()->getDataScore());
        }
        if (event.type == sf::Event::MouseMoved) {
            const auto mousePos = sf::Mouse::getPosition(*scene->getWindow());
            scene->getSceneGameplay()->gunRotate(static_cast<sf::Vector2f>(mousePos));
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            scene->getSceneGameplay()->gunShot({static_cast<float>(event.mouseButton.x),
                                                static_cast<float>(event.mouseButton.y)});
        }
    }

}

void HandlerSceneGameplay::update(GameWorld *scene)
{
    scene->update();
    scene->getSceneGameplay()->update();
    scene->getSceneGameplay()->draw(scene->getWindow());
    if (scene->getSceneGameplay()->gameOver()) {
        scene->getGameState()->changed(GameState::State::Score);
        scene->getSceneGameplay()->gameStop();
        scene->getGameState()->setScore(scene->getSceneGameplay()->getDataScore());
    }
}

void HandlerSceneGameplay::render(GameWorld *scene)
{
    scene->render();
}

}