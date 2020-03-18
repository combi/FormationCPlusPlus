//!
//! @file DisplayBoard.hpp
//! @brief All functionnalities around the displayed board.
//! @date 01/02/2020
//! @author jbruel
//!

#ifndef DISPLAYBOARD_HPP
# define DISPLAYBOARD_HPP

# include "Game/MapSize.hpp"
# include <array>

# define MAP_V_CHAR		 '|'
# define MAP_H_CHAR	     '-'
# define MAP_INSIDE_CHAR ' '

void	displayBoard(const std::array<char, MAP_SIZE> &gameMap);

#endif /** DISPLAYBOARD_HPP **/
