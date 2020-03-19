/*
 * GameLogic.cpp
 *
 *  Created on: Feb 29, 2020
 *      Author: combi

        Value
Up Key    72
Down Key  80
Right Key 77
Left Key  75


La facon de gerer le framerate: https://stackoverflow.com/a/38730986

*/


#include <Game/Map.hpp>
#include "Game/DisplayBoard.hpp"
#include "Game/GameLogic.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <set>
#include <deque>
#include <math.h>

#include <stdio.h>
#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>

//#define RANDOMIZE (rand() % (GAMEMAP_SIZE-3)) + 1
//#define RANDOM_CELL_INDEX rand() % ((GAMEMAP_SIZE*GAMEMAP_SIZE) + 1)
//#define RANDOM_COORDS {rand() % (GAMEMAP_SIZE + 1),rand() % (GAMEMAP_SIZE + 1)}
#define RANDOM_COORD rand() % (GAMEMAP_SIZE)  // la map fait 30 de large, mais les index vont de 0 a 29 donc on ne veut pas d'index == 30 !!!

typedef std::pair<unsigned short, unsigned short> _pair_;


bool
snakeEatsFruit(_pair_ cellCoord, std::set<_pair_> &food, unsigned short &score)
{
	bool result = false;

	std::set<_pair_>::iterator it;
	it = food.find(cellCoord);
	if(it != food.end())
	{
		_pair_ found = *it;
		result = true;

		_pair_ newFood = found;
		while( (newFood == found) || (newFood == cellCoord) )
		{
			newFood = {RANDOM_COORD, RANDOM_COORD};
		}
		food.erase(found);
		food.insert(newFood);
//		std::cout << "Added food here (" << newFood.first << "," << newFood.second << ")" << std::endl;
		score ++;
	}

	return result;
}


void advanceSnake(std::deque<_pair_> &snake, _pair_ newCoord, bool eatsFruit, bool &snakeIsAlive)
{
	_pair_ c;
    for (unsigned i=0; i<snake.size(); i++)
	{
    	c = snake.at(i);
    	if(c == newCoord)
    	{
    		snakeIsAlive = false;
    		break;
    	}
	}
    if (snakeIsAlive)
    {
		snake.push_front(newCoord);
		if(!eatsFruit)
		{
			snake.pop_back();
		}
    }

}


void printFoodDetails(std::set<_pair_> food)
{
	_pair_ c;
	std::cout << "Food details:";
	for (std::set<_pair_>::iterator it=food.begin(); it!=food.end(); ++it)
	{
		c = *it;
		std::cout << " (" << c.first << "," << c.second << ")";
	}
	std::cout << std::endl;
}

void printSnakeDetails(std::deque<_pair_> snake)
{
	_pair_ c;
    std::cout << "Snake details:";
    for (std::deque<_pair_>::iterator it = snake.begin(); it!=snake.end(); ++it)
	{
		c = *it;
		std::cout << " (" << c.first << "," << c.second << ")";
	}
	std::cout << std::endl;
	std::cout << "front: {" << snake.front().first << "," << snake.front().second << "}" << std::endl;
	std::cout << "back: {" << snake.back().first << "," << snake.back().second << "}" << std::endl;
//	std::cout << "back:" << snake.back() << std::endl;

}

void getNewDir(char userInput, char &snakeDir)
{
	switch (userInput)
	{
		case 'w':
			if (snakeDir != 's')
			{
				snakeDir = 'n';
			}
			break;
		case 's':
			if (snakeDir != 'n')
			{
				snakeDir = 's';
			}
			break;
		case 'a':
			if (snakeDir != 'e')
			{
				snakeDir = 'w';
			}
			break;
		case 'd':
			if (snakeDir != 'w')
			{
				snakeDir = 'e';
			}
			break;
	}
}

void play()
{
	srand(0);

//	MAP --------------------------------------
//	Comme la map est constituee maintenant uniquement de caracteres vides
//	et qu'on dessine son bord avec ncurses, on n'a plus besoin d'avoir un <array> de char
//	La procedure de display affichera uniquement les caracteres de snake / food aux
//	bonnes positions

//    const unsigned short numCells = GAMEMAP_SIZE*GAMEMAP_SIZE;
//    std::array<char, numCells> board;
//    board.fill(' ');
//
//  FOOD --------------------------------------
    std::set<_pair_> food;

    while(food.size()<INIT_FOOD_NUM)
    {
    	food.insert({RANDOM_COORD, RANDOM_COORD});
    }
    printFoodDetails(food);

//  SNAKE --------------------------------------
    std::deque<_pair_> snake;
    snake.push_front({0,0});
    snake.push_front({1,0});
    snake.push_front({2,0});

    printSnakeDetails(snake);



//  PLAY --------------------------------------

    initscr();

    noecho();
    nodelay(stdscr, TRUE);
    start_color();
    curs_set(0);


    WINDOW * win = newwin(GAMEMAP_SIZE+2, GAMEMAP_SIZE+2, (LINES-GAMEMAP_SIZE)/2, (COLS-GAMEMAP_SIZE)/2);
    box(win, 0, 0);

    unsigned short x = snake.front().first;
    unsigned short y = snake.front().second;
    unsigned short score = 0;

    _pair_ currCoord;
    _pair_ lastSnakeEnd;

    bool snakeIsAlive = true;
    int userInput = 0;
    char snakeDir = 's';

    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();

    unsigned short hertz = 7;

    displayBoard(win, snake, food, lastSnakeEnd);

    bool doPlay = true;
    while (doPlay && snakeIsAlive && userInput != 27)  // 27 = Escape
    {
    	next_frame += std::chrono::milliseconds(1000 / hertz);
    	if ((userInput= getch()) == ERR)
    	{
			/* user hasn't responded
			...
			*/
    	}
    	else
    	{
    		getNewDir(userInput, snakeDir);
    	}

		switch (snakeDir)
		{
			case 'e':
				x++;
				break;
			case 'w':
				x--;
				break;
			case 'n':
				y--;
				break;
			case 's':
				y++;
				break;
		}


		if ((x < 0) || (x > GAMEMAP_SIZE-1) || (y < 0) || (y > GAMEMAP_SIZE-1))
		{
			snakeIsAlive= false;
		}

		currCoord = {x, y};

		/* avant de mettre a jour le snake on memorise son extremite, pour updater le board
		 * car ca nous permettra de ne pas avoir a tout redessiner. Il suffit de remplacer l'extremite du snake par une case vide, car
		 * il ne peut rien a y avoir d'autre. et ensuite inserer les fruits et le snake dans le board.
        */
		lastSnakeEnd = snake.back();

		if (snakeIsAlive)
		{
			if (snakeEatsFruit(currCoord, food, score))
			{
				advanceSnake(snake, currCoord, true, snakeIsAlive);
//				hertz ++;

			}
			else
			{
				advanceSnake(snake, currCoord, false, snakeIsAlive);
			}
		}

		displayBoard(win, snake, food, lastSnakeEnd);


	    refresh();
	    wrefresh(win);
    	std::this_thread::sleep_until(next_frame);
    }

    displayGameOver(win);
    wrefresh(win);

//    getch();
    char zz;
    std::cin >> zz;
    endwin();
}
