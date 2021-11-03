//Written by Vincent Wilson 2021

#ifndef GRID_H
#define GRID_H

#include <string>
#include "Tile.h"

class Grid {

private:

	int width;

	int height;

	int m_numMines;

	Tile*** tiles;

	void expand(int x, int y);

public:

	Grid();

	~Grid();

	void create(int w, int h, int numMines);

	void update();

	void reveal(int x, int y);

	void highlight(int x, int y);

	void flag(int x, int y);

	void display();

	bool checkWin();

	void destroy();
};

#endif