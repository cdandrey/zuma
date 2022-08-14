/******************************************************************************
**
** File      HandlerSceneScore.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "HandlerSceneScore.h"
#include "../../controls/GameScenes.h"
#include "../../controls/GameState.h"

#include <SFML/Graphics.hpp>

namespace zuma {

bool HandlerSceneScore::isOpen(GameScenes *scene) const
{
    return scene->isOpen();
}

void HandlerSceneScore::Input(GameScenes *scene) 
{
    sf::Event event;
    while (scene->getWindow()->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            scene->getWindow()->close();
        }
        if (event.type == sf::Event::MouseMoved) {
            const auto mousePos = sf::Mouse::getPosition(*scene->getWindow());
            scene->getSceneScore()->ButtonOkMouseHover(mousePos);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (scene->getSceneScore()->ButtonOkMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getGameState()->changed(GameState::State::Menu);
            }
        }
    }
}

void HandlerSceneScore::Update(GameScenes *scene)
{
    scene->Update();
    scene->getSceneScore()->Draw(scene->getWindow());
}

void HandlerSceneScore::Render(GameScenes *scene)
{
    scene->Render();
}

}