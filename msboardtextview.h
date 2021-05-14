#ifndef msboardtextview_h
#define msboardtextview_h

#include "minesweeper.h"

class MSBoardTextView {
        MinesweeperBoard & game;
        int height;
        int width;
public:
	explicit MSBoardTextView (MinesweeperBoard & game);
	void display();
};

#endif //msboardtextview_h
