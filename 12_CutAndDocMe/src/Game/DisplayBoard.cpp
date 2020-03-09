/*
 * DisplayBoard.cpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */


#include "Game/DisplayBoard.hpp"

#include <iostream>

void displayBoard(Parameters gameParams)
{

    int size      = gameParams.size;
    char outsideH = gameParams.outsideH;
    char outsideV = gameParams.outsideV;
    char inside   = gameParams.inside;

    // ON DESSINE LE CARRE

    char toPrint = 0;
    for (int y=0; y<size; y++)
    {
        for (int x=0; x<size; x++)
        {
        	if ((y == 0) || (y==size-1))
        	{
        		toPrint = outsideH;
        	}
        	else
        	{
            	if ((x == 0) || (x==size-1))
            	{
            		toPrint = outsideV;
            	}
            	else
            	{
            		toPrint = inside;
            	}
        	}

            std::cout << toPrint;
		}

        std::cout << "\n";

    }
}

