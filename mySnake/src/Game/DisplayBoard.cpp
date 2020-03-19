/*
 * DisplayBoard.cpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */

#include "Game/Map.hpp"
#include "Game/DisplayBoard.hpp"

#include <iostream>

typedef std::pair<unsigned short, unsigned short> _pair_;

void displayBoard(WINDOW * win, std::deque<_pair_> snake, std::set<_pair_> food, _pair_ lastSnakeEnd, unsigned short score)
{

	move(((LINES-GAMEMAP_SIZE)/2)-1, (COLS-GAMEMAP_SIZE)/2);
	addstr("Score:");
	std::string s = std::to_string(score);
	char const *scoreChar = s.c_str();
	addstr(scoreChar);

	// erase last snake tail cell
    chtype chEmpty = MAP_INSIDE_CHAR;
	wmove(win, lastSnakeEnd.second+1, lastSnakeEnd.first+1);
	waddch(win, chEmpty);

	// Update head
    chtype chSnakeHead = SNAKE_HEAD_CHAR;
    _pair_ head = snake.front();
	wmove(win, head.second+1, head.first+1);
	waddch(win, chSnakeHead);

	// Update tail
	_pair_ c;
    chtype chSnakeTail = SNAKE_TAIL_CHAR;
    for (std::deque<_pair_>::iterator it = snake.begin()+1; it!=snake.end(); ++it)
	{
		c = *it;
		wmove(win, c.second+1, c.first+1);
//		waddch(win, chSnakeTail| COLOR_PAIR(2));
		waddch(win, chSnakeTail);
	}


    chtype chFood= MAP_FOOD_CHAR;
	for (std::set<_pair_>::iterator it=food.begin(); it!=food.end(); ++it)
	{
		c = *it;
		wmove(win, c.second+1, c.first+1);
//		waddch(win, chSnakeTail| COLOR_PAIR(2));
		waddch(win, chFood);
	}
}

void displayGameOver(WINDOW * win)
{
	std::string gameOver = "GAME OVER";
	wmove(win, GAMEMAP_SIZE/4, ((GAMEMAP_SIZE-gameOver.length())/2) +1 );
	waddstr(win, gameOver.c_str());
}
