/******************************************************************************
**
** File      HandlerSceneMenu.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/
#include <iostream>

#include "HandlerSceneMenu.h"
#include "Scene.h"
#include "../GameState.h"

#include <SFML/Graphics.hpp>

namespace zuma {

bool HandlerSceneMenu::isOpen(Scene *scene) const
{
    return scene->isOpen();
}

void HandlerSceneMenu::Input(Scene *scene) 
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
            scene->getMainMenu()->ButtonPlayMouseHover(mousePos);
            scene->getMainMenu()->ButtonExitMouseHover(mousePos);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

            if (scene->getMainMenu()->ButtonPlayMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getGameState()->changed(GameState::State::Play);
            }

            if (scene->getMainMenu()->ButtonExitMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getWindow()->close();
            }
        }
    } 
}

void HandlerSceneMenu::Update(Scene *scene)
{
    scene->Update();
    scene->getMainMenu()->Draw(scene->getWindow());
}

void HandlerSceneMenu::Render(Scene *scene)
{
    scene->Render();
}

}