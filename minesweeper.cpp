#include <iostream>
#include <cmath>
#include "minesweeper.h"

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode) {

	this -> width = 5;
	this -> height = 5;
	moves = 0;
	this -> mode = HARD;
	for (int row = 0; row < height + 1; row++) {
		for (int col = 0; col < width + 1; col++) {
			board[row][col].hasMine = false;
			board[row][col].hasFlag = false;
			board[row][col].isRevealed = false;
		}
	}
	mines_left = set_mines(height, width, mode);
	moves_left = (width * height) - mines_left;
};

int MinesweeperBoard::getBoardWidth() const {
	return width;
}

int MinesweeperBoard::getMovesLeft() const {
	return (moves_left - moves);
}

int MinesweeperBoard::getBoardHeight() const {
	return height;
}

int MinesweeperBoard::getMineCount() const {
	return mines_left;
}

int MinesweeperBoard::set_mines(int height, int width, GameMode mode) {

	int mines_left = 0;
	float factor = 0;
	if (mode == DEBUG) {
		for (int col = 0; col < height; col++) {
			for (int row = 0; row < width; row++) {
				if (col == row) {
					board[col][row].hasMine = true;
				}
				if (col == 0) {
					board[col][row].hasMine = true;
				}
				if (row == 0 && col % 2 == 0) {
					board[col][row].hasMine = true;
				}
			}
		}
	} else {
		if (mode == EASY) {
			factor = 0.1;
		}
		if (mode == MEDIUM) {
			factor = 0.2;
		}
		if (mode == HARD) {
			factor = 0.3;
		}
		mines_left = round(height * width * factor);
		for (int i = 0; i < mines_left; i++) {
				int row = rand() % width;
				int col = rand() % height;
				if (board[col][row].hasMine == false) {
					board[col][row].hasMine = true;
				} else i--;
		}
	}
	return mines_left;
}

int MinesweeperBoard::countMines(int x, int y) const {

	if (board[x][y].isRevealed == false) return -1;
	if (x > width || y > height) return -1;
	int counter = 0;
	if (x - 1 > 0) {
		if (board[x - 1][y].hasMine == true) counter++;
	}
	if (x + 1 < width) {
		if (board[x + 1][y].hasMine == true) counter++;
	}
	if (y - 1 > 0) {
		if (board[x][y - 1].hasMine == true) counter++;
	}
	if (y + 1 < height) {
		if (board[x][y + 1].hasMine == true) counter++;
	}
	if (x + 1 < width && y + 1 < height) {
		if (board[x + 1][y + 1].hasMine == true) counter++;
	}
	if (x + 1 < width && y - 1 > 0) {
		if (board[x + 1][y - 1].hasMine == true) counter++;
	}
	if (x - 1 > 0 && y + 1 < height) {
		if (board[x - 1][y + 1].hasMine == true) counter++;
	}
	if (x - 1 > 0 && y - 1 > 0) {
		if (board[x - 1][y - 1].hasMine == true) counter++;
	}
	return counter;
}

bool MinesweeperBoard::isRevealed(int row, int col) const {

	if (board[row][col].isRevealed == true) return true;
	else return false;
}

bool MinesweeperBoard::hasFlag(int row, int col) const {

	if (board[row][col].hasFlag == false) return false;
	else if (board[row][col].isRevealed == true) return false;
	else if (row > width || col > height) return false;
	else return true;
}

void MinesweeperBoard::toggleFlag(int row, int col) {

	if (board[row][col].isRevealed == true) return;
	else if (row > width || col > height) return;
	else if (state == FINISHED_LOSS || state == FINISHED_WIN) return;
	else {
		if (board[row][col].hasFlag == false) {
			board[row][col].hasFlag = true;
			return;
		}
		if (board[row][col].hasFlag == true) {
			board[row][col].hasFlag = false;
			return;
		}
//		if (board[row][col].hasMine == board[row][col].hasFlag) {
//			mines_left--;
//			if (mines_left == 0) {
//				state = FINISHED_WIN;
//			}
//		}
	}
}

void MinesweeperBoard::revealField(int row, int col) {

	if (board[row][col].isRevealed == true) return;
	else if (row > width || col > height) return;
	else if (state == FINISHED_LOSS || state == FINISHED_WIN) return;
	else if (board[row][col].hasFlag) return;
	else {
		if (moves == 0 && mode != DEBUG) {
			board[row][col].hasMine = false;
			board[rand() % width + 1][rand() % height + 1].hasMine = true;
		}
		board[row][col].isRevealed = true;
		moves++;
		if (board[row][col].hasMine && moves > 0) {
			state = FINISHED_LOSS;
		}
	}
}

void MinesweeperBoard::debug_display() const {
	for (int col = 0; col < height; col++) {
		for (int row = 0; row < width; row++) {
			char mine, flag, revealed;
			if (board[col][row].hasMine == true) {
				mine = 'M';
			} else {
				mine = '.';
			}
			if (board[col][row].hasFlag == true) {
				flag = 'f';
			} else {
				flag = '.';
			}
			if (board[col][row].isRevealed == true) {
				revealed = 'o';
			} else {
				revealed = '.';
			}
			std::cout << "[" << mine << revealed << flag << "]";
		}
		std::cout << "\n";
	}
}

char MinesweeperBoard::getFieldInfo(int row, int col) const {

	char counted = countMines(row, col);
	if (row > width || col > height) return '#';
	else if (board[row][col].isRevealed == false && board[row][col].hasFlag == true) return 'F';
	else if (board[row][col].isRevealed == false && board[row][col].hasFlag == false) return '_';
	else if (board[row][col].isRevealed == true && board[row][col].hasMine == true) return 'x';
	else if (board[row][col].isRevealed == true && counted == 0) return ' ';
	else if (board[row][col].isRevealed == true && counted != 0) return counted;
	else return 0;
}

GameState MinesweeperBoard::getGameState() const {

	if (state == FINISHED_LOSS) return FINISHED_LOSS;
	else if (moves_left - moves == 0) return FINISHED_WIN;
	else if (state == RUNNING && mines_left == 0) return FINISHED_WIN;
	else return RUNNING;
}
