//Written by Vincent Wilson 2021

#include <iostream>
#include "Grid.h"

//function prototypes
bool isNumber(std::string str);

void getInput();

//Command argument variables
std::string arguments;

int numArgs;

std::string option, str_width, str_height, str_x, str_y, str_numMines;


int main() {

	bool success = true;

	bool validInput;

	bool newGame;

	int width, height, x, y, numMines;

	Grid field;

	system("clear");

	//input error checking
	do {

		validInput = false;

		system("clear");

		std::cout << "---------- M I N E S W E E P E R ----------\n\n";

		std::cout << "\n";

		std::cout << "Enter \"startgame\", width, height, and # of mines to begin game.\n\n";

		std::cout << "Example: \"startgame 5 5 6\"\n\n";

		std::cout << "command: ";

		//get user input
		getInput();

		if (numArgs == 4) {

			if (option.compare("startgame") == 0 && isNumber(str_width) && isNumber(str_height) && isNumber(str_numMines)) {

				//convert input strings to integers
				width = stoi(str_width);
				height = stoi(str_height);
				numMines = stoi(str_numMines);

				if (width < 2 || height < 2 || numMines <= 0 || numMines >= width * height) {

					validInput = false;
				}

				else {

					validInput = true;
				}
			}
		}

		else {

			validInput = false;
		}

		std::cout << "\n";

	} while (validInput == false);

	//start the game loop
	do {

		newGame = false;

		//create the playing field with specified number of mines
		field.create(width, height, numMines);

		//loop until game is won or lost
		while (success == true) {

			system("clear");

			//update the field
			field.update();

			//print the updated field to the console
			field.display();

			//input error checking
			do {

				validInput = false;

				system("clear");

				field.display();

				std::cout << "Enter one of the following commands to make a move:\n\n"

				<< "\"reveal\", \"highlight\", \"flag\"\n\n";

				std::cout << "Example: \"reveal 1 2\"\n\n";

				std::cout << "command: ";

				//get user input
				getInput();

				if (numArgs == 3) {

					if ((option.compare("reveal") == 0 || option.compare("highlight") == 0 || option.compare("flag") == 0) && isNumber(str_x) && isNumber(str_y)) {

						//convert input strings to integers
						x = stoi(str_x);
						y = stoi(str_y);

						if (x < 1 || x > width || y < 1 || y > height) {

							validInput = false;
						}

						else {

							validInput = true;
						}
					}
				}

				else if (numArgs == 4) {

					if ((option.compare("startgame") == 0) && isNumber(str_width) && isNumber(str_height) && isNumber(str_numMines)) {

						//convert input strings to integers
						width = stoi(str_width);
						height = stoi(str_height);
						numMines = stoi(str_numMines);

						if (width < 2 || height < 2 || numMines < 1 || numMines >= width * height) {

							validInput = false;
						}

						else {

							validInput = true;
						}
					}
				}

				else {

					validInput = false;
				}

				std::cout << "\n";

			} while (validInput == false);

			//handle commands here
			if (option.compare("reveal") == 0) {

				field.reveal(x, y);
			}

			if (option.compare("highlight") == 0) {

				field.highlight(x, y);
			}

			if (option.compare("flag") == 0) {

				field.flag(x, y);
			}

			if (option.compare("startgame") == 0) {

				newGame = true;
				
				//clean up the grid
				field.destroy();

				break;
			}

			//Check if game has been won
			success = field.checkWin();
		}

	} while (newGame == true);

	//clean up the grid
	field.destroy();

	return 0;
}

//check if input is a number
bool isNumber(std::string str) {

	for (int i = 0; i < str.length(); i++) {

		if (isdigit(str[i]) == false) {

			return false;
		}
	}

	return true;
}

//get user input as a linux-like command
void getInput() {

	numArgs = 1;

	int count = 0;

	option = str_width = str_height = str_x = str_y = str_numMines = "";

	getline(std::cin, arguments);

	int len = arguments.length();

	//get first argument
	for (int i = count; i < len; i++) {

		if (!isspace(arguments[i])) {

			option += arguments[i];

			count++;
		}

		else {

			numArgs++;;

			count++;

			break;
		}
	}

	//get second argument if present
	for (int i = count; i < len; i++) {

		if (!isspace(arguments[i])) {

			str_width += arguments[i];

			str_x += arguments[i];

			count++;
		}

		else {

			numArgs++;

			count++;

			break;
		}
	}

	//get third argument if present
	for (int i = count; i < len; i++) {

		if (!isspace(arguments[i])) {

			str_height += arguments[i];

			str_y += arguments[i];

			count++;
		}

		else {

			numArgs++;

			count++;

			break;
		}
	}

	//get fourth argument if present
	for (int i = count; i < len; i++) {

		if (!isspace(arguments[i])) {

			str_numMines += arguments[i];

			count++;
		}

		else {

			numArgs++;

			count++;

			break;
		}
	}

	//For testing purposes
	//std::cout << "Arguments: " << numArgs << " Option: " << option << " Width: " << str_width << " Height: " << str_height << " Mines: " << str_numMines << " XY: " << str_x << str_y << "\n\n";
}
