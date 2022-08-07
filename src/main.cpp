#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 800), "Zuma");

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                app.close();
            }
        }

        app.clear();
        app.display();
    }

    return 0;
}
