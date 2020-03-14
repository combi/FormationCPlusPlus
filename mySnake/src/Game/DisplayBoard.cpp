/*
 * DisplayBoard.cpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */


#include "Game/DisplayBoard.hpp"

#include <iostream>


void displayBoard(std::array<char, GAMEMAP_SIZE*GAMEMAP_SIZE> board)
{
	std::cout << std::endl;

//	char insideChar   = '@';
	char outsideCharH = '-';
	char outsideCharV = '|';

    int fullBoardSize = GAMEMAP_SIZE+2;
    int index;
    for (int y=0; y<fullBoardSize; y++)
    {
        for (int x=0; x<fullBoardSize; x++)
        {
        	if ((y == 0) || (y==fullBoardSize-1))
        	{
        		std::cout << outsideCharH;
        	}
        	else
        	{
            	if ((x == 0) || (x==fullBoardSize-1))
            	{
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

