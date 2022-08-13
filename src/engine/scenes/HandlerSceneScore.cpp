/******************************************************************************
**
** File      HandlerSceneScore.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "HandlerSceneScore.h"
#include "Scene.h"
#include "../GameState.h"

#include <SFML/Graphics.hpp>

namespace zuma {

bool HandlerSceneScore::isOpen(Scene *scene) const
{
    return scene->isOpen();
}

void HandlerSceneScore::Input(Scene *scene) 
{
    sf::Event event;
    while (scene->getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            scene->getWindow()->close();
        }
        if (event.type == sf::Event::MouseMoved) {
            const auto mousePos = sf::Mouse::getPosition(*scene->getWindow());
            scene->getScore()->ButtonOkMouseHover(mousePos);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (scene->getScore()->ButtonOkMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getGameState()->changed(GameState::State::Menu);
            }
        }
    }
}

void HandlerSceneScore::Update(Scene *scene)
{
    scene->Update();
    scene->getScore()->Draw(scene->getWindow());
}

void HandlerSceneScore::Render(Scene *scene)
{
    scene->Render();
}

}