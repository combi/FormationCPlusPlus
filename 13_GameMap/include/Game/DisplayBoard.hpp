#ifndef GAMEMAP_SIZE
#define GAMEMAP_SIZE  30
#endif

#ifndef INCLUDE_GAME_DISPLAYBOARD_HPP_
#define INCLUDE_GAME_DISPLAYBOARD_HPP_

#include<climits>
#include <array>


#define INSIDE_CHAR ' '
#define OUTSIDE_H_CHAR '-'
#define OUTSIDE_V_CHAR '|'
#define FOOD_CHAR 'O'
#define SNAKE_HEAD_CHAR 'S'
#define SNAKE_TAIL_CHAR '~'


void displayBoard(std::array<char, GAMEMAP_SIZE*GAMEMAP_SIZE> board);




#endif /* INCLUDE_GAME_DISPLAYBOARD_HPP_ */
