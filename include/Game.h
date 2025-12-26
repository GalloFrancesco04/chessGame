#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

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

    sf::RenderWindow window;
    static constexpr int BOARD_SIZE = 8;
    static constexpr int SQUARE_SIZE = 80;
};

#endif // GAME_H
