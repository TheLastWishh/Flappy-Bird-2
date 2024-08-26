#include "Pipe.hpp"

Pipe::Pipe(float x, float y, float space, const sf::Texture& texture) {
    pipeBottom.setTexture(texture);
    pipeTop.setTexture(texture);

    pipeBottom.setPosition(x, y + space);
    pipeBottom.setScale(1.5f, 1.5f);

    pipeTop.setPosition(x, y);
    pipeTop.setScale(1.5f, -1.5f);
}

void Pipe::move(float offsetX) {
    pipeBottom.move(offsetX, 0.f);
    pipeTop.move(offsetX, 0.f);
}

void Pipe::render(sf::RenderWindow& window) const {
    window.draw(pipeBottom);
    window.draw(pipeTop);
}

bool Pipe::intersects(const sf::Sprite& bird) const {
    return pipeBottom.getGlobalBounds().intersects(bird.getGlobalBounds()) ||
        pipeTop.getGlobalBounds().intersects(bird.getGlobalBounds());
}

bool Pipe::isOffScreen() const {
    return pipeBottom.getPosition().x < -pipeBottom.getGlobalBounds().width;
}
