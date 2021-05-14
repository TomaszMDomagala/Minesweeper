#ifndef mssfmlview_h
#define mssfmlview_h

#include <SFML/Graphics.hpp>
#include "minesweeper.h"

class MSSFMLView {
    MinesweeperBoard & game;
    int height;
    int width;
    int screen_width = 800;
    int screen_height = 800;
    sf::RectangleShape square;
public:
    explicit MSSFMLView (MinesweeperBoard & game);
    void drawOnWindow (sf::RenderWindow & win);
};

#endif //mssfmlview_h
