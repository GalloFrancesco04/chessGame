#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"

class Game
{
public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void drawBoard();
    void drawCoordinates();
    void handleBoardClick(int row, int col);

    sf::RenderWindow window;
    sf::Font font;
    bool hasFont{false};
    sf::Texture piecesTexture;
    bool hasTexture{false};
    static constexpr int BOARD_SIZE = 8;
    static constexpr int SQUARE_SIZE = 80;
    static constexpr int PIECE_SIZE = 60; // Spritesheet is 360x120 (6 cols x 2 rows of 60x60)
    Board board;
    bool hasSelection = false;
    int selectedRow;
    int selectedColumn;
    chess::Square selectedSquare;
};

#endif // GAME_H
