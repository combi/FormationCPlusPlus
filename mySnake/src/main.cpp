//!
//! @file main.cpp
//! @brief Snake game main function. Entry point.
//! @date 01/02/2020
//! @author jbruel
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
//
//#include <iostream>
//#include <chrono>
//#include <thread>
//
//int main()
//{
//    using clock = std::chrono::steady_clock;
//
//    auto next_frame = clock::now();
//
//    while(true)
//    {
//        next_frame += std::chrono::milliseconds(1000 / 5); // 5Hz
//
//        // do stuff
//        std::cout << std::time(0) << '\n'; // 5 for each second
//
//        // wait for end of frame
//        std::this_thread::sleep_until(next_frame);
//
//
//    }
//}
