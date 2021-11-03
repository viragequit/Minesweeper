//Written by Vincent Wilson 2021

#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {

private:

	bool is_a_mine = false;

	bool isHidden = true;

	bool isFlagged = false;

	bool isHighlighted = false;

	std::string symbol;

	int numAdjacent = 0;

public:

	Tile();

	~Tile();

	void update();

	void addMine();

	void addHint();

	void reveal();

	void flag();

	bool hasFlag();

	void highlight();

	bool hasMine();

	bool hidden();

	int getHint();

	std::string display();
};

#endif