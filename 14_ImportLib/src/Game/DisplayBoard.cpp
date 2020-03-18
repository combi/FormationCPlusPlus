//!
//! @file DisplayBoard.cpp
//! @brief All functionnalities around the displayed board.
//! @date 01/02/2020
//! @author jbruel
//!

#include "Game/DisplayBoard.hpp"
#include <iostream>
#include <ncurses.h>


void displayBoard(const std::array<char, MAP_SIZE> &gameMap)
{
	unsigned short idx = 0;

	for (size_t y = 0; y < 32; ++y)
	{
		for (size_t x = 0; x < 32; ++x)
		{
			move(y, x);
			if (x == 0 || x > 30)
				addch(MAP_V_CHAR);
			else if (y == 0 || y > 30)
				addch(MAP_H_CHAR);
			else
				addch(gameMap[idx++]);
		}
	}
	move(32, 0);

	refresh();
}
