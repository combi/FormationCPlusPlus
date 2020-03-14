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

//    std::fill_n(boardChars, numCells, board.insideChar);

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
            		else
            		{
            			boardChars[index] = board.insideChar;
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
    	boardCellIndex = snake.path[snakeBodyIndex].x + (snake.path[snakeBodyIndex ].y*boardSize);
    	boardChars[boardCellIndex] = snake.tailChar;
    }
    int headCellIndex = snake.head.x + (snake.head.y*boardSize);
	boardChars[headCellIndex] = snake.headChar;


    // ON DESSINE LE BOARD
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


void displayBoard2(std::array<char, GAMEMAP_SIZE*GAMEMAP_SIZE> board)
{
	std::cout << std::endl;

//	char insideChar   = '@';
	char outsideCharH = '-';
	char outsideCharV = '|';

//    int numCells = board.size();
    int fullBoardSize = GAMEMAP_SIZE+2;
    int index;
    for (int y=0; y<fullBoardSize; y++)
    {
        for (int x=0; x<fullBoardSize; x++)
        {
        	if ((y == 0) || (y==fullBoardSize-1))
        	{
//        		boardChars[index] = board.outsideCharH;
        		std::cout << outsideCharH;
        	}
        	else
        	{
            	if ((x == 0) || (x==fullBoardSize-1))
            	{
//            		boardChars[index] = board.outsideCharV;
            		std::cout << outsideCharV;
            	}
            	else
            	{
            		index = (x-1) + ((y-1)*GAMEMAP_SIZE);
            		std::cout << board[index];
            	}
        	}
		}
		std::cout << std::endl;
    }
}

