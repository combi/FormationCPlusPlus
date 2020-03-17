#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../include/Help.hpp"

void printHelp()
{
	//std::cerr << "ERROR! You must specify a square size and a character for the outline\n";
	std::cout << "Usage : ./snake [--help]" << std::endl;
	std::cout << std::endl;
	std::cout << "Snake is the common name for a video game concept where the player maneuvers a" << std::endl;
	std::cout << "line which grows in length, with the line itself being a primary obstacle." << std::endl;
}

void printInviteForHelp()
{
	std::cerr << "Try 'helpMe --help' for more information." << std::endl;

}

