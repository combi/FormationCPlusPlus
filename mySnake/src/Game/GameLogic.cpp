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


#define RANDOMIZE (rand() % (board.size-3)) + 1

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



void play()
{
	srand(0);

    Board board;

    board.size = 25;
    board.fruit.x = RANDOMIZE;
    board.fruit.y = RANDOMIZE;

    board.insideChar   = ' ';
    board.outsideCharH = '-';
    board.outsideCharV = '|';
    board.fruitChar    = '@';

    Snake snake;
    snake.headChar = 'O';
    snake.tailChar = 'o';
    snake.head.x   = RANDOMIZE;
    snake.head.y   = RANDOMIZE;
    snake.dir      = 'n';
    snake.length   = 1;
    snake.numMoves = 0;
    snake.alive    = true;

//    unsigned short numCells = board.size*board.size;


	snake.path[0].x = snake.head.x;
	snake.path[0].y = snake.head.y;

    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();


    char userInput = 0;
    unsigned short hertz = 4;

    while (snake.alive)
    {
    	next_frame += std::chrono::milliseconds(1000 / hertz);

    	if (true)
    	{
    		if (kbhit())
			{
    			userInput = getchar();
				//Up Key    72
				//Down Key  80
				//Right Key 77
				//Left Key  75


				switch (userInput)
				{
					case 'w':
//					case 72:
						if (snake.dir == 's')
						{
							snake.alive = false;
						}
						else
						{
							snake.dir = 'n';
						}
						break;
					case 's':
//					case 80:
						if (snake.dir == 'n')
						{
							snake.alive = false;
						}
						else
						{
							snake.dir = 's';
						}
						break;
					case 'a':
//					case 75:
						if (snake.dir == 'e')
						{
							snake.alive = false;
						}
						else
						{
							snake.dir = 'w';
						}
						break;
					case 'd':
//					case 77:
						if (snake.dir == 'w')
						{
							snake.alive = false;
						}
						else
						{
							snake.dir = 'e';
						}
						break;
				}
    		}
			if (snake.alive)
			{
				snakeAdvance(snake);
			}

			if ((snake.head.x == 0) || (snake.head.x == board.size-1) || (snake.head.y == 0) || (snake.head.y == board.size-1))
			{
				snake.alive= false;
			}

			if (snakeEatsFruit(snake, board.fruit.x, board.fruit.y))
			{
				board.fruit.x = RANDOMIZE;
				board.fruit.y = RANDOMIZE;
				hertz += 1;
			}
//        	snake.path[recordId].x = snake.head.x;
//        	snake.path[recordId].y = snake.head.y;
        	snake.path[snake.numMoves].x = snake.head.x;
        	snake.path[snake.numMoves].y = snake.head.y;
        	snake.numMoves ++;

			std::cout.flush();
			displayBoard(board, snake);

			if (!snake.alive)
			{
				std::cout << "Game over. Press any key to exit." << std::endl;
			}
			else
			{
				std::cout << "Enter WASD (move the snake) or Esc (quit) and press 'enter':" << std::endl;
//				std::cin >> userInput;
//				std::cout << userInput << std::endl;
			}
    	}

    	std::this_thread::sleep_until(next_frame);

    }
}
