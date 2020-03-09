/*
 * DisplayBoard.cpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */


#include "Game/DisplayBoard.hpp"

#include <iostream>

void displayBoard(Board board, Snake snake)
{

    int boardSize  = board.size;

    // ON DESSINE LE CARRE

//    char toPrint = 0;
    for (int y=0; y<boardSize; y++)
    {
        for (int x=0; x<boardSize; x++)
        {

        	if ((y == 0) || (y==boardSize-1))
        	{
//        		toPrint = board.outsideCharH;
        		std::cout << board.outsideCharH;
        	}
        	else
        	{
            	if ((x == 0) || (x==boardSize-1))
            	{
//            		toPrint = board.outsideCharV;
            		std::cout << board.outsideCharV;
            	}
            	else
            	{
            		if ((x==snake.head.x) &&(y==snake.head.y))
            		{
//            			toPrint = snake.headChar;
//            			toPrint = snake.length;
            			std::cout << snake.length;

            		}
            		else if ((x==board.fruit.x) &&(y==board.fruit.y))
            		{
//            			toPrint = board.fruitChar;
            			std::cout << board.fruitChar;
            		}
            		else
            		{
//            			toPrint = board.insideChar;
            			std::cout << board.insideChar;
            		}

            	}
        	}

//            std::cout << toPrint;
		}

        std::cout << std::endl;

    }
}

