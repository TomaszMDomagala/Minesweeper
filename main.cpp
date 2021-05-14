#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "minesweeper.h"
#include "msboardtextview.h"
#include "mstextcontroller.h"
#include "mssfmlview.h"

int main(void) {

	srand(time(NULL));

	constexpr int screen_width = 800;
	constexpr int screen_height = 800;
	sf::RenderWindow win(sf::VideoMode(screen_width, screen_height), "Minesweeper");
	win.setVerticalSyncEnabled(true);
	MinesweeperBoard board (5, 5, HARD);
	MSSFMLView view (board);
//	MSBoardTextView viewtext (board);
//	MSTextController ctrl (board, viewtext);

	board.debug_display();

	while(win.isOpen()) {
		sf::Event event;
		while(win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				win.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
    			if (event.mouseButton.button == sf::Mouse::Right) {
					board.toggleFlag(event.mouseButton.y*board.getBoardHeight()/screen_height, event.mouseButton.x*board.getBoardWidth()/screen_width);
    			}
				if (event.mouseButton.button == sf::Mouse::Left) {
					board.revealField(event.mouseButton.y*board.getBoardHeight()/screen_height, event.mouseButton.x*board.getBoardWidth()/screen_width);
    			}
			}
		}
		win.clear(sf::Color(100, 100, 100));
		view.drawOnWindow(win);
		win.display();
	}

	return 0;
}
