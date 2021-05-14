#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "mssfmlview.h"

MSSFMLView::MSSFMLView(MinesweeperBoard & game) : game(game) {
    height = game.getBoardHeight();
    width = game.getBoardWidth();
    square.setSize(sf::Vector2f(screen_width/width - 10, screen_height/height - 10));
}

void MSSFMLView::drawOnWindow(sf::RenderWindow & win) {

    sf::Font font;
    if (!font.loadFromFile("/home/thomas/Documents/Cppkurs/minesweeper/VeraSe.ttf")) {
        std::cout << "Error";
    }

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);

    for (int h = 0; h < height; h++) {
        int hpos = 5 + ((screen_height/height)*h);
        for (int w = 0; w < width; w++) {
            int wpos = 5 + ((screen_width/width)*w);
            int info = game.getFieldInfo(h, w);
            if (info > 9) {
                if ((char)info == '_') {
                    square.setFillColor(sf::Color(200, 200, 200));
                }
                if ((char)info == 'F') {
                    square.setFillColor(sf::Color(200, 0, 0));
                }
                if ((char)info == 'x') {
                    square.setFillColor(sf::Color::Black);
                }
                if ((char)info == ' ') {
                    square.setFillColor(sf::Color(100, 100, 100));
                }
            } else {
                std::string s = std::to_string(info);
                text.setString(s);
                text.setPosition(((screen_width/width)*w) + ((screen_width/width)/4) + width, ((screen_height/height)*h) + ((screen_height/height)/4));
                square.setFillColor(sf::Color(100, 100, 100));
            }

            square.setPosition(wpos, hpos);
            win.draw(square);
            win.draw(text);
        }
    }
    if (game.getMovesLeft() == 0) {
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        text.setCharacterSize(50);
        text.setPosition(0, 0);
        text.setString("You won!");
        win.draw(text);
    }
    if (game.getGameState() == FINISHED_LOSS) {
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        text.setCharacterSize(50);
        text.setPosition(0, 0);
        text.setString("You lost!");
        win.draw(text);
    }
}
