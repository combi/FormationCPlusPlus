//!
//! @file main.cpp
//! @brief Snake game main function. Entry point.
//! @date 01/02/2020
//! @author jbruel
//!
//!
#include "Game/GameLogic.hpp"
#include "Help.hpp"

#include <iostream>
#include <cstdlib>


int	main(int argc, char *argv[])
{
	const std::string helpFlag= "--help";

    for(int i = 1; i < argc; i++ ) {
    	if ( std::string(argv[i]) == helpFlag )
    	{
    		printHelp();
    		return 1;
    	}
    }

    play();


    return (EXIT_SUCCESS);
}
