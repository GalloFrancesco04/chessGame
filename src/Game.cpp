#include "Game.h"
#include <vector>
#include <string>

Game::Game() : window(sf::VideoMode(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE), "Chess Game")
{
    window.setFramerateLimit(60);

    // Try loading a commonly available font; fall back to assets if provided
    const std::vector<std::string> candidates = {
        // Project-local fonts
        "assets/fonts/DejaVuSans.ttf",
        "assets/fonts/NotoSans-Regular.ttf",
        "../assets/fonts/DejaVuSans.ttf",
        "../assets/fonts/NotoSans-Regular.ttf",
        // Common system paths (Arch/others)
        "/usr/share/fonts/noto/NotoSans-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/LiberationSans-Regular.ttf"};
    for (const auto &p : candidates)
    {
        if (font.loadFromFile(p))
        {
            hasFont = true;
            break;
        }
    }
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
    drawCoordinates();
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

void Game::drawCoordinates()
{
    if (!hasFont)
    {
        return; // No font available; skip drawing labels
    }

    // Files: a–h along the bottom (white perspective)
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        sf::Text t;
        t.setFont(font);
        t.setString(std::string(1, static_cast<char>('a' + col)));
        t.setCharacterSize(16);
        t.setFillColor(sf::Color::White);
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(1.0f);

        float x = static_cast<float>(col * SQUARE_SIZE + 6);
        float y = static_cast<float>(BOARD_SIZE * SQUARE_SIZE - 20);
        t.setPosition(x, y);
        window.draw(t);
    }

    // Ranks: 8–1 along the left side (white perspective)
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        sf::Text t;
        t.setFont(font);
        t.setString(std::to_string(BOARD_SIZE - row));
        t.setCharacterSize(16);
        t.setFillColor(sf::Color::White);
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(1.0f);

        float x = 4.0f;
        float y = static_cast<float>(row * SQUARE_SIZE + 4);
        t.setPosition(x, y);
        window.draw(t);
    }
}
