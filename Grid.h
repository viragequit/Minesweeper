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
	
	//Divide and CONQUER!
	
	/*void expandTopLeft(int x, int y);
	
	void expandTopMiddle(int x, int y);
	
	void expandTopRight(int x, int y);
	
	void expandMiddleLeft(int x, int y);
	
	void expandMiddleRight(int x, int y);
	
	void expandBottomLeft(int x, int y);
	
	void expandBottomMiddle(int x, int y);
	
	void expandBottomRight(int x, int y);*/
	
	void addHints();

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
	
	void printWinScreen();
	
	void printLoseScreen(int x, int y);
};

#endif
