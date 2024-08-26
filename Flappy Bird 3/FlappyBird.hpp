#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Pipe.hpp"

class FlappyBird {
public:
    FlappyBird(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);
    void update();
    void render();

private:
    sf::RenderWindow& window;
    sf::Texture bgTexture, flappyTexture, pipeTexture;
    sf::Sprite background, bird;
    std::vector<sf::Sprite> pipes;
    float gravity, frame, space;
    int count, score;
    bool gameover, add;
    sf::Font font;
    sf::Text txt_score, txt_gameover;

    void movePipes();
    void setAnimeBird();
    void moveBird();
    void resetGame();
};
