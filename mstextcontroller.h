#ifndef mstextcontroller_h
#define mstextcontroller_h

#include "minesweeper.h"
#include "msboardtextview.h"

class MSTextController {
    MinesweeperBoard & game;
    MSBoardTextView & view;
public:
    MSTextController (MinesweeperBoard & game, MSBoardTextView & view);
    void play();
};

#endif //mstextcontroller_h
