/*
 * DisplayBoard.hpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */

#ifndef INCLUDE_GAME_DISPLAYBOARD_HPP_
#define INCLUDE_GAME_DISPLAYBOARD_HPP_



struct Parameters
{
    int size ;
    char outsideH;
    char outsideV;
    char inside;
};

void displayBoard(Parameters gameParams);




#endif /* INCLUDE_GAME_DISPLAYBOARD_HPP_ */
