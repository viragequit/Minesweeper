//Written by Vincent Wilson 2021

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Grid.h"


//default constructor
Grid::Grid() {


}

//default destructor
Grid::~Grid() {


}

//set up the playing field grid according to user input
void Grid::create(int w, int h, int numMines) {

	width = w;

	height = h;

	m_numMines = numMines;

	//create tile array
	tiles = new Tile * *[width];

	//add rows to the grid
	for (int i = 0; i < width; i++) {

		Tile** tile_row = new Tile * [height];

		tiles[i] = tile_row;
	}

	//add tiles to the grid
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			Tile* tile = new Tile();

			tiles[j][i] = tile;
		}
	}

	//Generate random seed
	srand(time(NULL));

	//randomize the mines
	int count = 0;
	int x, y;

	while (count < m_numMines) {

		x = rand() % width;
		y = rand() % height;

		if (tiles[x][y]->hasMine() == false) {

			tiles[x][y]->addMine();

			count++;
		}
	}

	//create tile hints
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			//check tile to the left
			if (j - 1 > -1) {

				if (tiles[j - 1][i]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}

			//check tile diagonal top/left
			if (j - 1 > -1 && i - 1 > -1) {

				if (tiles[j - 1][i - 1]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}

			//check tile above
			if (i - 1 > -1) {

				if (tiles[j][i - 1]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}

			//check tile diagonal top/right
			if (j + 1 < width && i - 1 > -1) {

				if (tiles[j + 1][i - 1]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}

			//check tile to the right
			if (j + 1 < width) {

				if (tiles[j + 1][i]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}

			//check tile diagonal bottom/right
			if (j + 1 < width && i + 1 < height) {

				if (tiles[j + 1][i + 1]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}

			//check tile below
			if (i + 1 < height) {

				if (tiles[j][i + 1]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}

			//check tile diagonal bottom/left
			if (j - 1 > -1 && i + 1 < height) {

				if (tiles[j - 1][i + 1]->hasMine()) {

					tiles[j][i]->addHint();
				}
			}
		}
	}
}

void Grid::update() {

	//traverse y
	for (int i = 0; i < height; i++) {

		//traverse x
		for (int j = 0; j < width; j++) {

			//update tile's symbol
			tiles[j][i]->update();
		}
	}
}

void Grid::reveal(int x, int y) {

	if (tiles[x - 1][y - 1]->hasMine() == true) {

		system("clear");

		//reveal all mines on the field
		for (int i = 0; i < height; i++) {

			for (int j = 0; j < width; j++) {

				if (tiles[j][i]->hasMine() == true) {

					tiles[j][i]->reveal();
				}
			}
		}

		//update the field
		update();

		//print field to screen
		display();

		std::cout << "Mine hit at position " << x << ", " << y << "!\n\n";

		std::cout << "---------- G A M E  O V E R ! ----------\n\n";

		destroy();

		exit(0);
	}

	tiles[x - 1][y - 1]->reveal();

	//if tile was a zero, expand the field. Show adjacent zeros
	if (tiles[x - 1][y - 1]->getHint() == 0) {

		expand(x - 1, y - 1);
	}
}

//show adjacent zeros recursively
void Grid::expand(int x, int y) {

	//check tile to the left
	if (x - 1 > -1) {

		if (tiles[x - 1][y]->getHint() == 0 && tiles[x - 1][y]->hidden() == true && tiles[x - 1][y]->hasMine() == false) {

			tiles[x - 1][y]->reveal();

			expand(x - 1, y);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x - 1][y]->hasMine() == false) {

			tiles[x - 1][y]->reveal();
		}
	}

	//check tile diagonal top/left
	if (x - 1 > -1 && y - 1 > -1) {

		if (tiles[x - 1][y - 1]->getHint() == 0 && tiles[x - 1][y - 1]->hidden() == true && tiles[x - 1][y - 1]->hasMine() == false) {

			tiles[x - 1][x - 1]->reveal();

			expand(x - 1, y - 1);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x - 1][y - 1]->hasMine() == false) {

			tiles[x - 1][y - 1]->reveal();
		}
	}

	//check tile above
	if (y - 1 > -1) {

		if (tiles[x][y - 1]->getHint() == 0 && tiles[x][y - 1]->hidden() == true && tiles[x][y - 1]->hasMine() == false) {

			tiles[x][y - 1]->reveal();

			expand(x, y - 1);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x][y - 1]->hasMine() == false) {

			tiles[x][y - 1]->reveal();
		}
	}

	//check tile diagonal top/right
	if (x + 1 < width && y - 1 > -1) {

		if (tiles[x + 1][y - 1]->getHint() == 0 && tiles[x + 1][y - 1]->hidden() == true && tiles[x + 1][y - 1]->hasMine() == false) {

			tiles[x + 1][y - 1]->reveal();

			expand(x + 1, y - 1);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x + 1][y - 1]->hasMine() == false) {

			tiles[x + 1][y - 1]->reveal();
		}
	}

	//check tile to the right
	if (x + 1 < width) {

		if (tiles[x + 1][y]->getHint() == 0 && tiles[x + 1][y]->hidden() == true && tiles[x + 1][y]->hasMine() == false) {

			tiles[x + 1][y]->reveal();

			expand(x + 1, y);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x + 1][y]->hasMine() == false) {

			tiles[x + 1][y]->reveal();
		}
	}

	//check tile diagonal bottom/right
	if (x + 1 < width && y + 1 < height) {

		if (tiles[x + 1][y + 1]->getHint() == 0 && tiles[x + 1][y + 1]->hidden() == true && tiles[x + 1][y + 1]->hasMine() == false) {

			tiles[x + 1][y + 1]->reveal();

			expand(x + 1, y + 1);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x + 1][y + 1]->hasMine() == false) {

			tiles[x + 1][y + 1]->reveal();
		}
	}

	//check tile below
	if (y + 1 < height) {

		if (tiles[x][y + 1]->getHint() == 0 && tiles[x][y + 1]->hidden() == true && tiles[x][y + 1]->hasMine() == false) {

			tiles[x][y + 1]->reveal();

			expand(x, y + 1);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x][y + 1]->hasMine() == false) {

			tiles[x][y + 1]->reveal();
		}
	}

	//check tile diagonal bottom/left
	if (x - 1 > -1 && y + 1 < height) {

		if (tiles[x - 1][y + 1]->getHint() == 0 && tiles[x - 1][y + 1]->hidden() == true && tiles[x - 1][y + 1]->hasMine() == false) {

			tiles[x - 1][y + 1]->reveal();

			expand(x - 1, y + 1);
		}

		//if tile is not a mine and greater than zero, reveal the tile and end recursion
		if (tiles[x - 1][y + 1]->hasMine() == false) {

			tiles[x - 1][y + 1]->reveal();
		}
	}
}

void Grid::highlight(int x, int y) {
	
	tiles[x - 1][y - 1]->highlight();
}

void Grid::flag(int x, int y) {

	tiles[x - 1][y - 1]->flag();
}

//print the entire grid to the console
void Grid::display() {

	int rows = 0;

	int cols = 0;

	//traverse y
	for (int i = 0; i < height; i++) {

		//print y coordinates
		std::cout << rows + 1 << "		";

		//traverse x
		for (int j = 0; j < width; j++) {

			//print tile
			std::cout << tiles[j][i]->display() << "   ";
		}

		std::cout << "\n\n";

		rows++;
	}

	std::cout << "\n\n\n\n" << "		";

	//print x coordinates
	for (int k = 0; k < width; k++) {

		std::cout << cols + 1 << "   ";

		cols++;
	}

	std::cout << "\n\n";
}

bool Grid::checkWin() {

	int count = 0;

	int numSafeTiles = (width * height) - m_numMines;

	int safeTilesRevealed = 0;

	//count tiles that have been flagged and tiles that have been revealed
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			if (tiles[j][i]->hasMine() == true && tiles[j][i]->hasFlag() == true) {

				count++;
			}

			if (tiles[j][i]->hidden() == false) {
				
				safeTilesRevealed++;
			}
		}
	}
	
	//check if all safe tiles have been revealed and all mines have been flagged
	if (count == m_numMines && safeTilesRevealed == numSafeTiles) {

		system("clear");

		//update the field
		update();

		//print field to screen
		display();

		std::cout << "---------- Y O U  W I N ! ----------\n\n";

		return false;
	}

	return true;
}

void Grid::destroy() {

	//traverse y
	for (int i = 0; i < height; i++) {

		//traverse x
		for (int j = 0; j < width; j++) {

			//remove tile from memory
			delete tiles[j][i];
		}
	}

	//remove row arrays
	for (int i = 0; i < width; i++) {

		delete[] tiles[i];
	}

	//remove grid array
	delete[] tiles;
}
