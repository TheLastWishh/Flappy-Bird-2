#pragma once
#include <SFML/Graphics.hpp>
#include "FlappyBird.hpp"

class App {
public:
    App();
    void run();

private:
    sf::RenderWindow window;
    FlappyBird flappyBird;

    void processEvents();
    void update();
    void render();
};
