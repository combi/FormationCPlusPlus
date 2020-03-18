//!
//! @file GameLogic.cpp
//! @brief Snake game logic is develop here.
//! @date 01/02/2020
//! @author jbruel
//!

#include "Game/DisplayBoard.hpp"
#include "Game/LoadMap.hpp"
#include <iostream>
#include <ncurses.h>

void play(void)
{
	char input = '\0';

	std::array<char, MAP_SIZE>	gameMap;
	std::vector<unsigned short>	snake;
	std::vector<unsigned short>	food;

	snake   = loadSnake();
	food    = loadFood();
	gameMap = loadMap(snake, food);

	while (input != 27)
	{
		displayBoard(gameMap);
		addstr("Enter any character and press 'enter' : ");
		input = getch();
	}
}
