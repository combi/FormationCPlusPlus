//!
//! @file Help.cpp
//! @brief Help system for the Snake application.
//! @date 01/02/2020
//! @author jbruel
//!

#include <iostream>

void	showHelp(const char *appName)
{
	std::cout << "Usage : " << appName << " [ --help ]" << std::endl;
	std::cout << std::endl;
	std::cout << "Snake is the common name for a video game concept where the player maneuvers a line which grows in length, with the line itself being a primary obstacle." << std::endl;
}
