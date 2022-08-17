/******************************************************************************
**
** File      HandlerSceneMenu.cpp
** Author    Andrii Sydorenko
**
******************************************************************************/

#include "HandlerSceneMenu.h"
#include "../../controls/GameWorld.h"
#include "../../controls/GameState.h"

#include <SFML/Graphics.hpp>

namespace zuma {

bool HandlerSceneMenu::isOpen(GameWorld *scene) const
{
    return scene->isOpen();
}

void HandlerSceneMenu::input(GameWorld *scene) 
{
    sf::Event event;
    while (scene->getWindow()->pollEvent(event)) {
        
        scene->input(event);

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            scene->getGameState()->changed(GameState::State::Play);
        }
        
        if (event.type == sf::Event::MouseMoved) {
            const auto mousePos = sf::Mouse::getPosition(*scene->getWindow());
            scene->getSceneMainMenu()->buttonPlayMouseHover(mousePos);
            scene->getSceneMainMenu()->buttonExitMouseHover(mousePos);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

            if (scene->getSceneMainMenu()->buttonPlayMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getGameState()->changed(GameState::State::Play);
                scene->getSceneGameplay()->gameStart();
            }

            if (scene->getSceneMainMenu()->buttonExitMouseClick({event.mouseButton.x,event.mouseButton.y})) {
                scene->getWindow()->close();
            }
        }
    } 
}

void HandlerSceneMenu::update(GameWorld *scene)
{
    scene->update();
    scene->getSceneMainMenu()->draw(scene->getWindow());
}

void HandlerSceneMenu::render(GameWorld *scene)
{
    scene->render();
}

}