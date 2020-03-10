/*
 * DisplayBoard.hpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */

#ifndef INCLUDE_GAME_DISPLAYBOARD_HPP_
#define INCLUDE_GAME_DISPLAYBOARD_HPP_

#include<climits>

struct Coordinates
{
	unsigned short x;
	unsigned short y;
};

struct Board
{
	unsigned short size ;
    Coordinates fruit;
    char outsideCharH;
    char outsideCharV;
    char insideChar;
    char fruitChar;
};

struct Snake
{
    Coordinates head;
    Coordinates path[USHRT_MAX];  // 65535 ?
//    Coordinates path[5000];
    int length;
    char headChar;
    char tailChar;
    bool alive;
    char dir;
    int numMoves;
};



void displayBoard(Board board, Snake snake);




#endif /* INCLUDE_GAME_DISPLAYBOARD_HPP_ */
