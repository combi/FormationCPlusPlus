#include "Game/GameLogic.hpp"
#include "Game/DisplayBoard.hpp"

#include <iostream>
#include <array>
#include <set>
#include <deque>


#define RANDOM_CELL_INDEX rand() % ((GAMEMAP_SIZE*GAMEMAP_SIZE) + 1)


bool
snakeEatsFruit(unsigned short cellIndex, std::set<unsigned short> &food, unsigned short &eatenFood)
{
	bool result = false;

	std::set<unsigned short>::iterator it;
	it = food.find(cellIndex);
	if(it != food.end())
	{
		unsigned short found = *it;
		result = true;

		unsigned short newFood = found;
		while((newFood == found) || (newFood == cellIndex)){
			newFood = RANDOM_CELL_INDEX;
		}
		food.erase(found);
		food.insert(newFood);

		eatenFood ++;
	}

	return result;
}

void updateBoard(std::array<char, GAMEMAP_SIZE*GAMEMAP_SIZE> &board, std::set<unsigned short> food, std::deque<unsigned short> snake, unsigned short lastSnakeEnd)
{
	// FILL WITH FOOD
	for (std::set<unsigned short>::iterator it=food.begin(); it!=food.end(); ++it)
	{
		board[*it] = FOOD_CHAR;
	}

	// FILL WITH SNAKE
	board[lastSnakeEnd] = INSIDE_CHAR;
	board[snake.front()] = SNAKE_HEAD_CHAR;
    for (std::deque<unsigned short>::iterator it = snake.begin()+1; it!=snake.end(); ++it)
    {
    	board[*it] = SNAKE_TAIL_CHAR;
    }
}

void printFoodDetails(std::set<unsigned short> food)
{
	std::cout << "Food:";
	for (std::set<unsigned short>::iterator it=food.begin(); it!=food.end(); ++it)
	{
		std::cout << ' ' << *it;
	}
	std::cout << std::endl;
}

void printSnakeDetails(std::deque<unsigned short> snake)
{
    std::cout << "Snake:";
    for (std::deque<unsigned short>::iterator it = snake.begin(); it!=snake.end(); ++it)
	{
		std::cout << ' ' << *it;
	}
	std::cout << std::endl;
}

void play()
{
	srand(0);

//	MAP --------------------------------------
    const unsigned short numCells = GAMEMAP_SIZE*GAMEMAP_SIZE;
    std::array<char, numCells> board;
    board.fill(' ');

//  FOOD --------------------------------------
    std::set<unsigned short> food;

    while(food.size()<INIT_FOOD_NUM)
    {
    	food.insert(RANDOM_CELL_INDEX);
    }
    printFoodDetails(food);

//  SNAKE --------------------------------------
    std::deque<unsigned short> snake;
    snake.push_front(0);
    snake.push_front(1);
    snake.push_front(2);

    printSnakeDetails(snake);

//  PLAY --------------------------------------
	unsigned short lastSnakeEnd;
    lastSnakeEnd = snake.back();
    updateBoard(board, food, snake, lastSnakeEnd);
	displayBoard(board);
}
