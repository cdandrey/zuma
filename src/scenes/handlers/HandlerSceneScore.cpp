/******************************************************************************
**
** File      HandlerSceneScore.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "HandlerSceneScore.h"
#include "../../controls/GameWorld.h"
#include "../../controls/GameState.h"

#include <SFML/Graphics.hpp>

namespace zuma {

bool HandlerSceneScore::isOpen(GameWorld *scene) const
{
    return scene->isOpen();
}

void HandlerSceneScore::input(GameWorld *scene) 
{
    sf::Event event;
    while (scene->getWindow()->pollEvent(event)) {

        scene->input(event);

        if (event.type == sf::Event::MouseMoved) {
            const auto mousePos = sf::Mouse::getPosition(*scene->getWindow());
            scene->getSceneScore()->buttonOkMouseHover(mousePos);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (scene->getSceneScore()->buttonOkMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getGameState()->changed(GameState::State::Menu);
            }
        }
    }
}

void HandlerSceneScore::update(GameWorld *scene)
{
    scene->update();
    scene->getSceneScore()->setScore(scene->getGameState()->getScore());
    scene->getSceneScore()->draw(scene->getWindow());
}

void HandlerSceneScore::render(GameWorld *scene)
{
    scene->render();
}

}