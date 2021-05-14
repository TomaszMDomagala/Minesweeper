#include <iostream>
#include <cstdlib>
#include "msboardtextview.h"

MSBoardTextView::MSBoardTextView (MinesweeperBoard & game) : game(game) {
    width = game.getBoardWidth() ;
    height = game.getBoardHeight() ;
};

void MSBoardTextView::display() {
    std::cout << " ";
    for (int row = 0; row < width; row++) {
        std::cout << "  " << row << "  ";
    }
    std::cout << '\n';
    for (int col = 0; col < height; col++) {
        std::cout << col;
        for (int row = 0; row < width; row++) {
            int info = (int)game.getFieldInfo(col, row);
            std::cout << "[ ";
            if (info > 9) {
                std::cout << (char)info;
            } else {
                std::cout << info;
            }
            std::cout << " ]";
        }
        std::cout << '\n';
    }

}
