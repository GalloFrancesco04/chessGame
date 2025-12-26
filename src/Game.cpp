#include "Game.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

Game::Game() : window(sf::VideoMode(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE), "Chess Game")
{
    window.setFramerateLimit(60);

    // Try loading a commonly available font; fall back to assets if provided
    const std::vector<std::string> candidates = {
        // Project-local fonts (actual files)
        "assets/fonts/NotoSans-VariableFont_wdth,wght.ttf",
        "assets/fonts/NotoSans-Italic-VariableFont_wdth,wght.ttf",
        "../assets/fonts/NotoSans-VariableFont_wdth,wght.ttf",
        "../assets/fonts/NotoSans-Italic-VariableFont_wdth,wght.ttf",
        // Alternative project-local names
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

    // Load pieces spritesheet
    const std::vector<std::string> spritesheet_candidates = {
        "assets/icons/pieces.png",
        "../assets/icons/pieces.png",
        "../../assets/icons/pieces.png"};
    for (const auto &p : spritesheet_candidates)
    {
        if (piecesTexture.loadFromFile(p))
        {
            hasTexture = true;
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

void Game::handleBoardClick(int row, int col)
{
    chess::Square test = board.getSquare(row, col);
    std::cout << "Clicked: row=" << row << " col=" << col
              << " piece=" << (int)test.piece
              << " color=" << (int)test.color
              << " isEmpty=" << (test.piece == chess::Piece::EMPTY) << std::endl;
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

        if (event.type == sf::Event::MouseButtonPressed)
        {
            // Get mouse position relative to the window (more reliable than event coordinates)
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Map pixel coordinates to world coordinates (handles window scaling)
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            int col = static_cast<int>(worldPos.x) / SQUARE_SIZE;
            int row = static_cast<int>(worldPos.y) / SQUARE_SIZE;

            std::cout << "Mouse: pixel(" << mousePos.x << "," << mousePos.y << ") "
                      << "world(" << worldPos.x << "," << worldPos.y << ") "
                      << "grid(" << row << "," << col << ")" << std::endl;

            if (row >= 0 && row < 8 && col >= 0 && col < 8)
            {
                handleBoardClick(row, col);
            }
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
    // Map piece types to spritesheet column indices
    const std::map<chess::Piece, int> pieceToColumn = {
        {chess::Piece::QUEEN, 0},
        {chess::Piece::KING, 1},
        {chess::Piece::ROOK, 2},
        {chess::Piece::KNIGHT, 3},
        {chess::Piece::BISHOP, 4},
        {chess::Piece::PAWN, 5}};

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // Draw square background
            sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            square.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);

            // Alternating colors: light and dark
            if ((row + col) % 2 == 0)
            {
                square.setFillColor(sf::Color(217, 193, 159));
            }
            else
            {
                square.setFillColor(sf::Color(121, 60, 42));
            }

            window.draw(square);

            // Draw piece if present
            chess::Square boardSquare = board.getSquare(row, col);
            if (boardSquare.piece != chess::Piece::EMPTY && hasTexture)
            {
                // Determine spritesheet row: 0 = BLACK, 1 = WHITE
                int sheetRow = (boardSquare.color == chess::Color::BLACK) ? 0 : 1;

                // Determine spritesheet column from piece type
                int sheetCol = 0;
                auto it = pieceToColumn.find(boardSquare.piece);
                if (it != pieceToColumn.end())
                {
                    sheetCol = it->second;
                }

                // Create sprite from spritesheet (60x60 per piece)
                sf::IntRect textureRect(sheetCol * PIECE_SIZE, sheetRow * PIECE_SIZE, PIECE_SIZE, PIECE_SIZE);
                sf::Sprite sprite(piecesTexture, textureRect);

                // Center and scale the sprite to fit the square
                sprite.setScale(static_cast<float>(SQUARE_SIZE) / PIECE_SIZE, static_cast<float>(SQUARE_SIZE) / PIECE_SIZE);
                sprite.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);

                window.draw(sprite);
            }
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
