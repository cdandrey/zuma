#include "HandlerSceneGameplay.h"
#include "Scene.h"
#include "../GameState.h"

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
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            scene->getGameState()->changed(GameState::State::Menu);
        }
    }

}

void HandlerSceneGameplay::Update(Scene *scene)
{
    scene->Update();
    scene->getGameplay()->Draw(scene->getWindow());
}

void HandlerSceneGameplay::Render(Scene *scene)
{
    scene->Render();
}

}