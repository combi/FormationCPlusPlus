/*
 * DisplayBoard.hpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */

#ifndef INCLUDE_GAME_DISPLAYBOARD_HPP_
#define INCLUDE_GAME_DISPLAYBOARD_HPP_

#include <array>
#include <deque>
#include <set>

#include <ncurses.h>

void displayBoard(WINDOW * win,
				  std::deque<std::pair<unsigned short, unsigned short>> snake,
				  std::set<std::pair<unsigned short, unsigned short>> food,
				  std::pair<unsigned short, unsigned short> lastSnakeEnd,
				  unsigned short score);

void displayGameOver(WINDOW * win);




#endif /* INCLUDE_GAME_DISPLAYBOARD_HPP_ */
