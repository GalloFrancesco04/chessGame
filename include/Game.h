#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game
{
public:
    struct Position
    {
        int row;
        int col;
    };

    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void drawBoard();
    void drawCoordinates();
    void handleBoardClick(int row, int col);
    bool kingCheck(const Board &board, chess::Color kingColor);

    // SFML Resources
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture piecesTexture;
    bool hasFont{false};
    bool hasTexture{false};

    // Game State
    Board board;
    chess::Color turn = chess::Color::WHITE;

    // Selection State
    bool hasSelection = false;
    Position selectedPos;
    chess::Square selectedSquare;

    // Last Move Tracking
    bool hasLastMove = false;
    Position lastMoveFrom;
    Position lastMoveTo;

    // Constants
    static const std::map<chess::Piece, int> pieceToColumn;
    const sf::Color LIGHT_SQUARE{217, 193, 159};
    const sf::Color DARK_SQUARE{121, 60, 42};
    const sf::Color LAST_MOVE_HIGHLIGHT{170, 200, 60};
    static constexpr int BOARD_SIZE = 8;
    static constexpr int SQUARE_SIZE = 80;
    static constexpr int PIECE_SIZE = 60; // Spritesheet is 360x120 (6 cols x 2 rows of 60x60)
    static constexpr int SELECTION_HIGHLIGHT_ALPHA = 90;
};
