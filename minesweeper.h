#ifndef minesweeper_h
#define minesweeper_h

enum GameMode {
	EASY,
	MEDIUM,
	HARD,
	DEBUG
};

enum GameState {
	RUNNING,
	FINISHED_WIN,
	FINISHED_LOSS
};

struct Field {
	bool hasMine;
	bool hasFlag;
	bool isRevealed;
};

class MinesweeperBoard {
	Field board[100][100];
	int width, height, mines_left, moves, moves_left;
	GameMode mode;
	GameState state;
public:
	GameState getGameState() const;
	bool hasFlag(int x, int y) const;
	bool isRevealed(int x, int y) const;
	void toggleFlag(int x, int y);
	int getBoardWidth() const;
	int getBoardHeight() const;
	int getMovesLeft() const;
	int getMineCount() const;
	int countMines(int x, int y) const;
	int set_mines(int height, int width, GameMode mode);
	char getFieldInfo(int x, int y) const;
	MinesweeperBoard(int width, int height, GameMode mode);
	void revealField(int x, int y);
	void debug_display() const;
};

#endif //minesweeperboard_h
