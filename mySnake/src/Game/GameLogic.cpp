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
#include <math.h>

#include <stdio.h>
#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>


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
snakeEatsFruit(unsigned short cellIndex, std::set<unsigned short> &food)
{
	bool result = false;

	std::set<unsigned short>::iterator it;
	it = food.find(cellIndex);
	if(it != food.end())
	{
		unsigned short found = *it;
		result = true;

		unsigned short newFood = found;
		while((newFood == found) || (newFood == cellIndex)){
			newFood = RANDOM_CELL_INDEX;
		}
		food.erase(found);
		food.insert(newFood);
	}

	return result;
}


void updateBoard(std::array<char, GAMEMAP_SIZE*GAMEMAP_SIZE> &board, std::set<unsigned short> food, std::deque<unsigned short> snake, bool snakeIsAlive)
{

	char insideChar    = '.';
	char foodChar      = '@';
	char snakeHeadChar = 'O';
	char snakeTailChar = 'o';


	unsigned short int index;
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

    if(!snakeIsAlive)
    {
    	std::string gameOver = " Game Over ";
    	unsigned short width = gameOver.length();
    	unsigned short x = floor((GAMEMAP_SIZE - width)/2);
    	unsigned short y = floor(GAMEMAP_SIZE/2)-1;

    	index = x + y*GAMEMAP_SIZE;
    	unsigned short j=0;
    	for(unsigned short i=0; i<width; i++)
    	{
    		board[index+i] = gameOver[j++];
    	}
    	std::cout << std::endl;
    }
}


void advanceSnake(std::deque<unsigned short> &snake, unsigned short newCellIndex, bool eatsFruit)
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

void getNewDir(char userInput, char &snakeDir, bool &snakeIsAlive)
{
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

void play()
{
	srand(0);

//	MAP --------------------------------------
    const unsigned short numCells = GAMEMAP_SIZE*GAMEMAP_SIZE;
    std::array<char, numCells> board;
    board.fill('.');

//  FOOD --------------------------------------
    std::set<unsigned short> food;

    while(food.size()<INIT_FOOD_NUM)
    {
    	food.insert(RANDOM_CELL_INDEX);
    }
    printFoodDetails(food);

//  SNAKE --------------------------------------
    std::deque<unsigned short> snake;
    snake.push_front(0);
    snake.push_front(1);
    snake.push_front(2);

    printSnakeDetails(snake);

//  PLAY --------------------------------------
    short x = 2;
    short y = 0;

    unsigned short currCellIndex;

    bool snakeIsAlive = true;
    char userInput = 0;
    char snakeDir = 'e';

    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();

    unsigned short hertz = 4;

    while (snakeIsAlive && userInput != 27)  // 27 = Escape
    {
    	next_frame += std::chrono::milliseconds(1000 / hertz);

		if (kbhit())
		{
			userInput = getchar();
			getNewDir(userInput, snakeDir, snakeIsAlive);
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
			if (snakeEatsFruit(currCellIndex, food))
			{
				advanceSnake(snake, currCellIndex, true);
				hertz ++;
			}
			else
			{
				advanceSnake(snake, currCellIndex, false);
			}
		}
		updateBoard(board, food, snake, snakeIsAlive);
		std::cout.flush();
		std::cout << "Enter WASD to move the snake or Esc to quit" << std::endl;
		displayBoard(board);


    	std::this_thread::sleep_until(next_frame);
    }
}
