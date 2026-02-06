#include "Game.h"
#include "moveValidator.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

// Map piece types to spritesheet column indices
const std::map<chess::Piece, int> Game::pieceToColumn = {
    {chess::Piece::QUEEN, 0},
    {chess::Piece::KING, 1},
    {chess::Piece::ROOK, 2},
    {chess::Piece::KNIGHT, 3},
    {chess::Piece::BISHOP, 4},
    {chess::Piece::PAWN, 5}};

Game::Game() : window(sf::VideoMode(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE), "Chess Game")
{
    window.setFramerateLimit(60);

    // Load font and pieces spritesheet from project assets
    if (font.loadFromFile("assets/fonts/NotoSans-VariableFont_wdth,wght.ttf"))
        hasFont = true;

    if (piecesTexture.loadFromFile("assets/icons/pieces.png"))
        hasTexture = true;
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

bool Game::kingCheck(const Board &board, chess::Color kingColor)
{
    Position kingPos;
    if (!findKingPosition(board, kingColor, kingPos))
        return false;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board.getSquare(i, j).piece != chess::Piece::EMPTY && board.getSquare(i, j).color != kingColor)
            {
                if (moveValidator::isValidMove(board, i, j, kingPos.row, kingPos.col))
                    return true;
            }
        }
    }

    return false;
}

bool Game::isCheckmate(const Board &board, chess::Color kingColor)
{
    if (!kingCheck(board, kingColor))
        return false;

    for (int fromRow = 0; fromRow < BOARD_SIZE; fromRow++)
    {
        for (int fromCol = 0; fromCol < BOARD_SIZE; fromCol++)
        {
            chess::Square fromSquare = board.getSquare(fromRow, fromCol);
            if (fromSquare.piece == chess::Piece::EMPTY || fromSquare.color != kingColor)
                continue;

            for (int toRow = 0; toRow < BOARD_SIZE; toRow++)
            {
                for (int toCol = 0; toCol < BOARD_SIZE; toCol++)
                {
                    if (!moveValidator::isValidMove(board, fromRow, fromCol, toRow, toCol))
                        continue;

                    Board tempBoard = board;
                    tempBoard.setSquare(toRow, toCol, fromSquare);
                    tempBoard.setSquare(fromRow, fromCol, chess::emptySquare);

                    if (!kingCheck(tempBoard, kingColor))
                        return false;
                }
            }
        }
    }

    return true;
}

bool Game::findKingPosition(const Board &board, chess::Color kingColor, Position &outPos) const
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            chess::Square square = board.getSquare(i, j);
            if (square.color == kingColor && square.piece == chess::Piece::KING)
            {
                outPos.row = i;
                outPos.col = j;
                return true;
            }
        }
    }
    return false;
}

void Game::handleBoardClick(int row, int col)
{
    chess::Square initialSquare = board.getSquare(row, col);
    std::cout << "Clicked: row=" << row << " col=" << col
              << " piece=" << (int)initialSquare.piece
              << " color=" << (int)initialSquare.color
              << " isEmpty=" << (initialSquare.piece == chess::Piece::EMPTY) << std::endl;

    // Case 1: already selected something
    if (hasSelection)
    {

        // Click on your own piece: change selection to that piece
        if (initialSquare.piece != chess::Piece::EMPTY && initialSquare.color == turn)
        {
            selectedPos.row = row;
            selectedPos.col = col;
            selectedSquare = initialSquare;
            return;
        }

        if (!moveValidator::isValidMove(board, selectedPos.row, selectedPos.col, row, col))
        {
            hasSelection = false;
            return;
        }

        // Move to empty square or opponent piece
        chess::Square capturedSquare = board.getSquare(row, col);
        Position prevLastMoveFrom = lastMoveFrom;
        Position prevLastMoveTo = lastMoveTo;
        bool prevHasLastMove = hasLastMove;

        lastMoveFrom = selectedPos;
        lastMoveTo = {row, col};
        hasLastMove = true;

        board.setSquare(row, col, selectedSquare);
        board.setSquare(selectedPos.row, selectedPos.col, chess::emptySquare);

        if (kingCheck(board, turn))
        {
            board.setSquare(selectedPos.row, selectedPos.col, selectedSquare);
            board.setSquare(row, col, capturedSquare);
            lastMoveFrom = prevLastMoveFrom;
            lastMoveTo = prevLastMoveTo;
            hasLastMove = prevHasLastMove;
            hasSelection = false;
            return;
        }

        hasSelection = false;
        turn = (turn == chess::Color::WHITE) ? chess::Color::BLACK : chess::Color::WHITE;
        hasCheckHighlight = kingCheck(board, turn);
        if (hasCheckHighlight)
        {
            findKingPosition(board, turn, checkKingPos);
            if (isCheckmate(board, turn))
            {
                std::cout << "Checkmate!" << std::endl;
            }
        }
        return;
    }

    // Case 2: no selection yet, select if it's your turn
    if (initialSquare.piece != chess::Piece::EMPTY && initialSquare.color == turn)
    {
        hasSelection = true;
        selectedPos.col = col;
        selectedPos.row = row;
        selectedSquare = initialSquare;
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
                square.setFillColor(LIGHT_SQUARE);
            }
            else
            {
                square.setFillColor(DARK_SQUARE);
            }

            window.draw(square);

            // Highlight last move (from and to squares)
            if (hasLastMove)
            {
                if ((row == lastMoveFrom.row && col == lastMoveFrom.col) ||
                    (row == lastMoveTo.row && col == lastMoveTo.col))
                {
                    sf::RectangleShape lastMoveHighlight(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                    lastMoveHighlight.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
                    lastMoveHighlight.setFillColor(sf::Color(LAST_MOVE_HIGHLIGHT.r, LAST_MOVE_HIGHLIGHT.g, LAST_MOVE_HIGHLIGHT.b, SELECTION_HIGHLIGHT_ALPHA));
                    window.draw(lastMoveHighlight);
                }
            }

            // Highlight selected square (if any)
            if (hasSelection && row == selectedPos.row && col == selectedPos.col)
            {
                sf::RectangleShape highlight(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                highlight.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
                highlight.setFillColor(sf::Color(255, 255, 0, SELECTION_HIGHLIGHT_ALPHA)); // soft yellow overlay
                window.draw(highlight);
            }

            // Highlight king in check
            if (hasCheckHighlight && row == checkKingPos.row && col == checkKingPos.col)
            {
                sf::RectangleShape checkHighlight(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                checkHighlight.setPosition(col * SQUARE_SIZE, row * SQUARE_SIZE);
                checkHighlight.setFillColor(sf::Color(CHECK_HIGHLIGHT.r, CHECK_HIGHLIGHT.g, CHECK_HIGHLIGHT.b, SELECTION_HIGHLIGHT_ALPHA));
                window.draw(checkHighlight);
            }

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
