//!
//! @file LoadMap.cpp
//! @brief Snake game map (load system).
//! @date 24/02/2020
//! @author jbruel
//!

#include "Game/LoadMap.hpp"
#include "Game/MapSize.hpp"
#include "Game/DisplayBoard.hpp"

std::array<char, MAP_SIZE>	loadMap(std::vector<unsigned short> snake, std::vector<unsigned short> food)
{
	std::array<char, MAP_SIZE> 	loadMap;
	unsigned short				idx = 0;

	for (unsigned short y = 0; y < 30; ++y)
		for (unsigned short x = 0; x < 30; ++x)
			loadMap[idx++] = MAP_INSIDE_CHAR;
	for (size_t i = 0; i < snake.size(); ++i)
		loadMap[snake[i]] = (i + 1 >= snake.size()) ? 'S' : '~';
	for (unsigned short pos : food)
		loadMap[pos] = 'O';
	return (loadMap);
}

std::vector<unsigned short>	loadSnake()
{
	std::vector<unsigned short>	snakePos;

	snakePos.push_back(0);
	snakePos.push_back(1);
	snakePos.push_back(2);
	return (snakePos);
}

std::vector<unsigned short>	loadFood()
{
	std::vector<unsigned short>	foodPos;

	foodPos.push_back(139);
	foodPos.push_back(386);
	foodPos.push_back(521);
	return (foodPos);
}
