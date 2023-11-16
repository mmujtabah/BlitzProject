#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

    sf::RectangleShape rectangle(sf::Vector2f(100.0f, 100.0f));
    rectangle.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw the rectangle
        window.draw(rectangle);

        window.display();
    }

    return 0;
}
