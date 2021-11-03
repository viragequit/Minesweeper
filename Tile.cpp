//Written by Vincent Wilson 2021

#include <iostream>
#include "Tile.h"

//default constructor
Tile::Tile() {


}

//default destructor
Tile::~Tile() {


}

//update tiles to print correct symbol
void Tile::update() {

	if (isHidden == true) {

		symbol = "X";
	}

	if (isHidden == false && is_a_mine == false) {

		symbol = std::to_string(numAdjacent);
	}

	if (isHidden == false && is_a_mine == true) {

		symbol = "!";
	}

	if (isFlagged) {

		symbol = "B";
	}

	if (isHighlighted) {

		symbol = "H";
	}
}

//make tile hold a mine
void Tile::addMine() {

	is_a_mine = true;
}

//tell tile how many mines are next to it
void Tile::addHint() {

	numAdjacent += 1;
}

//show what is hidden under the tile
void Tile::reveal() {

	isFlagged = false;
	
	isHighlighted = false;

	isHidden = false;
}

//flag the tile
void Tile::flag() {

	if (isHidden == true) {

		isFlagged = !isFlagged;

		if (isHighlighted == true) {

			isHighlighted = false;
		}
	}
}

//check if tile is flagged
bool Tile::hasFlag() {

	return isFlagged;
}

//highlight the tile - toggle on/off
void Tile::highlight() {

	if (isHidden == true) {

		isHighlighted = !isHighlighted;

		if (isFlagged == true) {

			isFlagged = false;
		}
	}
}

//check to see if tile has a mine
bool Tile::hasMine() {

	return is_a_mine;
}

//check to see if tile is hidden
bool Tile::hidden() {

	return isHidden;
}

//get hint about how many mines tile is touching
int Tile::getHint() {

	return numAdjacent;
}

//return tile's symbol to be printed
std::string Tile::display() {

	return symbol;
}