//!
//! @file main.cpp
//! @brief Snake game main function. Entry point.
//! @date 01/02/2020
//! @author jbruel
//!

#include "Help.hpp"
#include "Game/GameLogic.hpp"
#include <iostream>
#include <cstdlib>
#include <ncurses.h>

int	main(int argc, const char * const *argv)
{
	if (argc > 1)
	{
		if (std::string("--help") != std::string(argv[1]))
		{
			std::cerr << "ERROR! Unrecognized option : " << argv[1] << std::endl;
			return (EXIT_FAILURE);
		}
		showHelp(argv[0]);
		return (EXIT_SUCCESS);
	}
	initscr();

	play();

	endwin();
    return (EXIT_SUCCESS);
}
