/*
 * DisplayBoard.hpp
 *
 *  Created on: 5 mars 2020
 *      Author: formation
 */

#ifndef GAMEMAP_SIZE
#define GAMEMAP_SIZE  30
#endif

#ifndef INCLUDE_GAME_DISPLAYBOARD_HPP_
#define INCLUDE_GAME_DISPLAYBOARD_HPP_

#include<climits>
#include <array>

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
void displayBoard2(std::array<char, GAMEMAP_SIZE*GAMEMAP_SIZE> board);




#endif /* INCLUDE_GAME_DISPLAYBOARD_HPP_ */
