#include "Game.h"

Game::Game() : window(sf::VideoMode(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE), "Chess Game")
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Game::update()
{
    // Update game logic here
}

void Game::render()
{
    window.clear(sf::Color::Black);
    drawBoard();
    window.display();
}

void Game::drawBoard()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);

            // Alternating colors: white and black
            if ((row + col) % 2 == 0)
            {
                square.setFillColor(sf::Color(217, 193, 159));
            }
            else
            {
                square.setFillColor(sf::Color(121, 60, 42));
            }

            window.draw(square);
        }
    }
}
