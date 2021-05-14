#include <iostream>
#include <cstdlib>
#include "mstextcontroller.h"

MSTextController::MSTextController (MinesweeperBoard & game, MSBoardTextView & view) : game(game), view(view) {

}

void MSTextController::play() {
    while(game.getGameState() == RUNNING) {
        unsigned int col = 0, row = 0;
        char option;
        std::cout << "r = Reveal\tf = Flag\n";
        std::cin >> option;
        std::cout << "Row: ";
        std::cin >> row;
        std::cout << "Col: ";
        std::cin >> col;
        if(option == 'r'){
            game.revealField(row, col);
        } else if (option == 'f') {
            game.toggleFlag(row, col);
        } else {
            std::cout << "Wrong input!\n";
        }
        std::system("clear");
        view.display();
    }
    if(game.getGameState() == FINISHED_WIN) {
        std::cout << '\n' << "You won!\n";
    } else if (game.getGameState() == FINISHED_LOSS) {
        std::cout << '\n' << "You lost\n";
    } else {
        std::cout << "Error";
    }
}
