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


#include "Game/GameLogic.hpp"
#include "Game/DisplayBoard.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <set>
#include <deque>

#include <stdio.h>
#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>
//#include <stdbool.h>

int kbhit(void) {
    static bool initflag = false;
    static const int STDIN = 0;

    if (!initflag) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initflag = true;
    }

    int nbbytes;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
}


#define RANDOMIZE (rand() % (GAMEMAP_SIZE-3)) + 1
#define RANDOM_CELL_INDEX rand() % ((GAMEMAP_SIZE*GAMEMAP_SIZE) + 1)

bool
snakeEatsFruit(Snake &snake, int x, int y)
{
	bool result = false;

	if ((snake.head.x == x) && (snake.head.y == y))
		{
			snake.length += 1;
			result = true;
		}
	return result;
}

bool
snakeEatsFruit2(unsigned short cellIndex, std::set<unsigned short> food)
{
	bool result = false;

	if(food.find(cellIndex) != food.end())
	{
		result = true;
	}

	return result;
}



void
snakeAdvance(Snake &snake)
{
	switch (snake.dir)
	{
		case 'e':
			snake.head.x += 1;
			break;
		case 'w':
			snake.head.x -= 1;
			break;
		case 'n':
			snake.head.y -= 1;
			break;
		case 's':
			snake.head.y += 1;
			break;
	}
}

void updateBoard2(std::array<char, GAMEMAP_SIZE*GAMEMAP_SIZE> &board, std::set<unsigned short> food, std::deque<unsigned short> snake)
{

	char insideChar    = '.';
	char foodChar      = '@';
	char snakeHeadChar = 'O';
	char snakeTailChar = 'o';


	int index;
	for (int y=0; y<GAMEMAP_SIZE; y++)
	{
		for (int x=0; x<GAMEMAP_SIZE; x++)
		{
			index = x + y*GAMEMAP_SIZE;
			if(food.find(index) != food.end())
			{
				board[index] = foodChar;
			}
			else
			{
				board[index] = insideChar;
			}
		}
	}
	board[snake.front()] = snakeHeadChar;
    for (std::deque<unsigned short>::iterator it = snake.begin()+1; it!=snake.end(); ++it)
    {
    	board[*it] = snakeTailChar;
    }
}


void advanceSnake2(std::deque<unsigned short> &snake, unsigned short newCellIndex, bool eatsFruit)
{
//	std::cout << "Advancing snake to " << newCellIndex<< std::endl;
    snake.push_front(newCellIndex);
    if(!eatsFruit)
    {
    	snake.pop_back();
    }
}


void printFoodDetails(std::set<unsigned short> food)
{
	std::cout << "Food:";
	for (std::set<unsigned short>::iterator it=food.begin(); it!=food.end(); ++it)
	{
		std::cout << ' ' << *it;
	}
	std::cout << std::endl;
}

void printSnakeDetails(std::deque<unsigned short> snake)
{
    std::cout << "Snake:";
    for (std::deque<unsigned short>::iterator it = snake.begin(); it!=snake.end(); ++it)
	{
		std::cout << ' ' << *it;
	}
	std::cout << std::endl;
}

void play()
{
	srand(0);

//	MAP --------------------------------------
    const unsigned short numCells = GAMEMAP_SIZE*GAMEMAP_SIZE;
    std::array<char, numCells> board2;
    board2.fill('.');

//  FOOD --------------------------------------
    std::set<unsigned short> food2;

    while(food2.size()<INIT_FOOD_NUM)
    {
    	food2.insert(RANDOM_CELL_INDEX);
    }
    printFoodDetails(food2);

//  SNAKE --------------------------------------
    std::deque<unsigned short> snake2;
    snake2.push_front(0);
    snake2.push_front(1);
    snake2.push_front(2);

    printSnakeDetails(snake2);

//  PLAY --------------------------------------
    short x = 2;
    short y = 0;

    unsigned short currCellIndex;

    bool snakeIsAlive = true;
    char userInput = 0;
    char snakeDir = 'e';

    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();

    unsigned short hertz = 6;

    while (snakeIsAlive)
    {
    	next_frame += std::chrono::milliseconds(1000 / hertz);

		if (kbhit())
		{
			userInput = getchar();
			switch (userInput)
			{
				case 'w':
					if (snakeDir == 's')
					{
						snakeIsAlive = false;
					}
					else
					{
						snakeDir = 'n';
					}
					break;
				case 's':
					if (snakeDir == 'n')
					{
						snakeIsAlive = false;
					}
					else
					{
						snakeDir = 's';
					}
					break;
				case 'a':
					if (snakeDir == 'e')
					{
						snakeIsAlive = false;
					}
					else
					{
						snakeDir = 'w';
					}
					break;
				case 'd':
					if (snakeDir == 'w')
					{
						snakeIsAlive = false;
					}
					else
					{
						snakeDir = 'e';
					}
					break;
			}
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

		currCellIndex = x + (y*GAMEMAP_SIZE);


		if (snakeIsAlive)
		{
			if (snakeEatsFruit2(currCellIndex, food2))
			{
				advanceSnake2(snake2, currCellIndex, true);
			}
			else
			{
				advanceSnake2(snake2, currCellIndex, false);
			}
		}
		updateBoard2(board2, food2, snake2);
		std::cout.flush();
		displayBoard2(board2);
		std::cout << "Enter WASD (move the snake) or Esc (quit) and press 'enter':" << std::endl;

    	if (userInput ==  27)
    	{
    		snakeIsAlive= false;
    	}

    	std::this_thread::sleep_until(next_frame);

    }
    std::cout << "Game over..." << std::endl;
}
