/******************************************************************************
**
** File      HandlerSceneMenu.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "HandlerSceneMenu.h"
#include "../../controls/GameScenes.h"
#include "../../controls/GameState.h"

#include <SFML/Graphics.hpp>

namespace zuma {

bool HandlerSceneMenu::isOpen(GameScenes *scene) const
{
    return scene->isOpen();
}

void HandlerSceneMenu::Input(GameScenes *scene) 
{
    sf::Event event;
    while (scene->getWindow()->pollEvent(event)) {
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            scene->getGameState()->changed(GameState::State::Play);
        }
        
        if (event.type == sf::Event::Closed) {
            scene->getWindow()->close();
        }

        if (event.type == sf::Event::MouseMoved) {
            const auto mousePos = sf::Mouse::getPosition(*scene->getWindow());
            scene->getSceneMainMenu()->ButtonPlayMouseHover(mousePos);
            scene->getSceneMainMenu()->ButtonExitMouseHover(mousePos);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

            if (scene->getSceneMainMenu()->ButtonPlayMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getGameState()->changed(GameState::State::Play);
            }

            if (scene->getSceneMainMenu()->ButtonExitMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getWindow()->close();
            }
        }
    } 
}

void HandlerSceneMenu::Update(GameScenes *scene)
{
    scene->Update();
    scene->getSceneMainMenu()->Draw(scene->getWindow());
}

void HandlerSceneMenu::Render(GameScenes *scene)
{
    scene->Render();
}

}