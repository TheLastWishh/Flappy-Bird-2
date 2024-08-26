#include "FlappyBird.hpp"
#include <iostream>

FlappyBird::FlappyBird(sf::RenderWindow& window)
    : window(window), gravity(0.f), frame(0.f), space(250.f), count(0), score(0),
    gameover(false), add(false)
{
    if (!bgTexture.loadFromFile("./resources/img/background.png") ||
        !flappyTexture.loadFromFile("./resources/img/flappy.png") ||
        !pipeTexture.loadFromFile("./resources/img/pipe.png")) {
        std::cerr << "Error: Could not load images!" << std::endl;
    }

    background.setTexture(bgTexture);
    bird.setTexture(flappyTexture);
    bird.setPosition(500.f - flappyTexture.getSize().x / 2.f, 300.f - flappyTexture.getSize().y / 2.f);
    bird.setScale(2.f, 2.f);
    bird.setTextureRect(sf::IntRect(0, 0, 34, 24));

    if (!font.loadFromFile("./resources/font/flappybird.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
    }

    txt_gameover.setFont(font);
    txt_gameover.setString("Press SPACE to restart");
    txt_gameover.setPosition(200, 300);
    txt_gameover.setCharacterSize(50);
    txt_gameover.setOutlineThickness(3);

    txt_score.setFont(font);
    txt_score.setString(std::to_string(score));
    txt_score.setPosition(10, 10);
    txt_score.setCharacterSize(50);
    txt_score.setOutlineThickness(3);
}

void FlappyBird::handleInput(const sf::Event& event) {
    if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        resetGame();
    }
}

void FlappyBird::update() {
    if (!gameover) {
        setAnimeBird();
        moveBird();
        movePipes();
        count = (count + 1) % 300;
    }
}

void FlappyBird::render() {
    window.draw(background);

    for (const auto& pipe : pipes) {
        window.draw(pipe);
    }

    window.draw(bird);

    if (gameover) {
        window.draw(txt_gameover);
    }

    window.draw(txt_score);
}

/*void FlappyBird::movePipes() {
    if (count % 150 == 0) {
        int pos = std::rand() % 275 + 175;

        sf::Sprite pipeBottom(pipeTexture);
        sf::Sprite pipeTop(pipeTexture);

        pipeBottom.setPosition(1000.f, pos + space);
        pipeTop.setPosition(1000.f, pos);
        pipeBottom.setScale(1.5f, 1.5f);
        pipeTop.setScale(1.5f, -1.5f);

        pipes.push_back(pipeBottom);
        pipes.push_back(pipeTop);
    }

    for (std::size_t i = 0; i < pipes.size(); ++i) {
        pipes[i].move(-3.f, 0.f);

        if (pipes[i].getGlobalBounds().intersects(bird.getGlobalBounds())) {
            bird.move(15.f, 0.f);
            bird.move(0.f, pipes[i].getScale().y < 0 ? -15.f : 15.f);
            gameover = true;
        }

        if (pipes[i].getPosition().x < -pipes[i].getGlobalBounds().width) {
            pipes.erase(pipes.begin() + i);
            --i;
        }
    }
}*/

void FlappyBird::movePipes() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        gravity = -8.f;
        bird.setRotation(-frame - 10.f);
    }
    else {
        bird.setRotation(frame - 10.f);
    }

    // Them cap pipe moi vao vector moi 150 frame
    if (count % 150 == 0) {
        int pos = std::rand() % 275 + 175;

        sf::Sprite pipeBottom(pipeTexture);
        sf::Sprite pipeTop(pipeTexture);

        pipeBottom.setPosition(1000.f, pos + space);
        pipeTop.setPosition(1000.f, pos);
        pipeBottom.setScale(1.5f, 1.5f);
        pipeTop.setScale(1.5f, -1.5f);

        pipes.push_back(pipeBottom);
        pipes.push_back(pipeTop);
    }

    bool pipePassed = false;

    for (std::size_t i = 0; i < pipes.size(); ++i) {
        pipes[i].move(-3.f, 0.f);

        if (pipes[i].getGlobalBounds().intersects(bird.getGlobalBounds())) {
            bird.move(15.f, 0.f);

            if (pipes[i].getScale().y < 0) {
                bird.move(0.f, -15.f);
            }
            else {
                bird.move(0.f, 15.f);
            }

            gameover = true;
        }

        if (pipes[i].getPosition().x < -pipes[i].getGlobalBounds().width) {
            pipes.erase(pipes.begin() + i);
            --i;
        }
        else if (pipes[i].getPosition().x == 448 && !add) {
            ++score;
            txt_score.setString(std::to_string(score));
            add = true;
        }
        else if (pipes[i].getPosition().x > 448) {
            add = false;
        }
    }
}

void FlappyBird::setAnimeBird() {
    frame += 0.15f;
    if (frame > 3) frame -= 3;
    bird.setTextureRect(sf::IntRect(34 * static_cast<int>(frame), 0, 34, 24));
}

void FlappyBird::moveBird() {
    bird.move(0.f, gravity);
    gravity += 0.5f;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        gravity = -8.f;
        bird.setRotation(-frame - 10.f);
    }
    else {
        bird.setRotation(frame - 10.f);
    }
}

void FlappyBird::resetGame() {
    score = 0;
    txt_score.setString(std::to_string(score));
    pipes.clear();

    bird.setPosition(500.f - flappyTexture.getSize().x / 2.f, 300.f - flappyTexture.getSize().y / 2.f);
    bird.setRotation(0.f);
    gravity = 0.f;
    gameover = false;
}
