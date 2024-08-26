#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:
    Pipe(float x, float y, float space, const sf::Texture& texture);
    void move(float offsetX);
    void render(sf::RenderWindow& window) const;

    bool intersects(const sf::Sprite& bird) const;
    bool isOffScreen() const;

private:
    sf::Sprite pipeBottom;
    sf::Sprite pipeTop;
};
