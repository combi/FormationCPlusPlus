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
    int numCells = boardSize*boardSize;
    char boardChars[numCells];

    std::fill_n(boardChars, numCells, board.insideChar);

    // ON CONSTRUIT LES CARACTERES REPRESENTATNT l'ETAT DU BOARD
    int index;
    for (int y=0; y<boardSize; y++)
    {
        for (int x=0; x<boardSize; x++)
        {
        	index = x + y*boardSize;

        	if ((y == 0) || (y==boardSize-1))
        	{
        		boardChars[index] = board.outsideCharH;
        	}
        	else
        	{
            	if ((x == 0) || (x==boardSize-1))
            	{
            		boardChars[index] = board.outsideCharV;
            	}
            	else
            	{
            		if ((x==snake.head.x) &&(y==snake.head.y))
            		{
//            			boardChars[index] = snake.length;
            			boardChars[index] = snake.headChar;

            		}
            		else if ((x==board.fruit.x) &&(y==board.fruit.y))
            		{
            			boardChars[index] = board.fruitChar;
            		}
            	}
        	}
		}
    }
    int boardCellIndex;
    int snakeBodyIndex;
    for (int i=0; i<snake.length; i++)
    {
    	snakeBodyIndex = snake.numMoves -1 - i;
//    	if (j>=snake.length)
//    	{
//    		break;
//    	}
    	boardCellIndex = snake.path[snakeBodyIndex].x + (snake.path[snakeBodyIndex ].y*boardSize);
    	boardChars[boardCellIndex] = '.';
    }


    // ON DESSINE LE CARRE
    for(int i=0; i<numCells; i++)
    {
		std::cout << boardChars[i];
		if(i && ((i+1)%boardSize) == 0)
		{
			std::cout << std::endl;
		}
    }
	std::cout << std::endl;
}

