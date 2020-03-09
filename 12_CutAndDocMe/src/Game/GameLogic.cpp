/*
 * GameLogic.cpp
 *
 *  Created on: Feb 29, 2020
 *      Author: combi
 */

#include "Game/GameLogic.hpp"
#include "Game/DisplayBoard.hpp"

#include <iostream>


void play()
{

    Parameters gameParams;


    gameParams.inside = ' ';
    gameParams.outsideH = '-';
    gameParams.outsideV = '|';
    gameParams.size = 30;

    char userInput = 0;
    while(userInput != 27)
    {
		displayBoard(gameParams);
		std::cout << "Enter any character and press 'enter':";
		std::cin >> userInput;
		std::cout << userInput;
    }
}
