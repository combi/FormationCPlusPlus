//!
//! @file LoadMap.hpp
//! @brief Snake game map (load system).
//! @date 24/02/2020
//! @author jbruel
//!

#ifndef LOADMAP_HPP
# define LOADMAP_HPP

# include "Game/MapSize.hpp"
# include <array>
# include <vector>

std::array<char, MAP_SIZE>	loadMap(std::vector<unsigned short> snake, std::vector<unsigned short> food);
std::vector<unsigned short>	loadSnake();
std::vector<unsigned short>	loadFood();

#endif /** LOADMAP_HPP **/
