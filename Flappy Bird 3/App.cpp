#include "App.hpp"

App::App()
    : window(sf::VideoMode(1000, 600), "Flappy Bird (Remix)", sf::Style::Titlebar | sf::Style::Close),
    flappyBird(window)
{
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0, 0));
}

void App::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void App::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        flappyBird.handleInput(event);
    }
}

void App::update() {
    flappyBird.update();
}

void App::render() {
    window.clear(sf::Color::Black);
    flappyBird.render();
    window.display();
}
