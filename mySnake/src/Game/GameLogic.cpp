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

*/


#include "Game/GameLogic.hpp"
#include "Game/DisplayBoard.hpp"

#include <iostream>


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
    board.fruitChar    = 'o';

    Snake snake;
    snake.headChar = 'x';
    snake.head.x   = RANDOMIZE;
    snake.head.y   = RANDOMIZE;
    snake.dir      = 's';
    snake.length   = 1;
    snake.numMoves = 0;
    snake.alive    = true;

    unsigned short numCells = board.size*board.size;
    Coordinates snakeRecords[numCells];


	snakeRecords[0].x = snake.head.x;
	snakeRecords[0].y = snake.head.y;

	snake.path[0].x = snake.head.x;
	snake.path[0].y = snake.head.y;

    char userInput = 0;
//    char userInput = 'w';
//    while(userInput != 27 && snake.alive)  // 27 is ascii code for Esc
//    {
//    	switch (userInput)
//    	{
//			case 'w':
//				if (snake.dir == 's')
//				{
//					snake.alive = false;
//				}
//				else
//				{
//					snake.dir = 'n';
//				}
//				break;
//			case 's':
//				if (snake.dir == 'n')
//				{
//					snake.alive = false;
//				}
//				else
//				{
//					snake.dir = 's';
//				}
//				break;
//			case 'a':
//				if (snake.dir == 'e')
//				{
//					snake.alive = false;
//				}
//				else
//				{
//					snake.dir = 'w';
//				}
//				break;
//			case 'd':
//				if (snake.dir == 'w')
//				{
//					snake.alive = false;
//				}
//				else
//				{
//					snake.dir = 'e';
//				}
//				break;
//    	}
//    	if (snake.alive)
//    	{
//			switch (snake.dir)
//			{
//				case 'e':
//					snake.head.x += 1;
//					break;
//				case 'w':
//					snake.head.x -= 1;
//					break;
//				case 'n':
//					snake.head.y -= 1;
//					break;
//				case 's':
//					snake.head.y += 1;
//					break;
//			}
//    	}
//
//    	if ((snake.head.x == 0) || (snake.head.x == board.size-1) || (snake.head.y == 0) || (snake.head.y == board.size-1))
//		{
//			snake.alive= false;
//		}
//
//		if (snakeEatsFruit(snake, board.fruit.x, board.fruit.y))
//		{
//		    board.fruit.x = RANDOMIZE;
//		    board.fruit.y = RANDOMIZE;
//		}
//
//
//
//		displayBoard(board, snake);
//
//		if (!snake.alive)
//		{
//			std::cout << "Game over. Press any key to exit." << std::endl;
//		}
//		else
//		{
//			std::cout << "Enter WASD (move the snake) or Esc (quit) and press 'enter':";
//			std::cin >> userInput;
//			std::cout << userInput << std::endl;
//		}
//    }
    int i = 0;
    int recordId = 0;
//    snake.alive = false;  // DEBUGONLY
    while (snake.alive)
    {
//    	i++;

//    	if (i%100000000 == 0)
    	if (i%200000000 == 0)
    	{
    		if (kbhit())
			{
    			userInput = getchar();

				switch (userInput)
				{
					case 'w':
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
//				switch (snake.dir)
//				{
//					case 'e':
//						snake.head.x += 1;
//						break;
//					case 'w':
//						snake.head.x -= 1;
//						break;
//					case 'n':
//						snake.head.y -= 1;
//						break;
//					case 's':
//						snake.head.y += 1;
//						break;
//				}
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
			}
			snakeRecords[recordId].x = snake.head.x;
        	snakeRecords[recordId].y = snake.head.y;

        	snake.path[recordId].x = snake.head.x;
        	snake.path[recordId].y = snake.head.y;
        	snake.numMoves ++;

        	recordId ++;
			std::cout.flush();
			displayBoard(board, snake);
//			std::cout.flush();

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

    	i++;

    }
}
