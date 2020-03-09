#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

// https://stackoverflow.com/questions/13145777/c-char-to-int-conversion


void printUsage()
{
	//std::cerr << "ERROR! You must specify a square size and a character for the outline\n";
	std::cout << "Usage : ./helpMe [--help] SIZE OUTSIDECHAR [INSIDECHAR]" << std::endl;
	std::cout << std::endl;
	std::cout << "Snake is the common name for a video game concept where the player maneuvers a" << std::endl;
	std::cout << "line which grows in length, with the line itself being a primary obstacle." << std::endl;
	std::cout << std::endl;
	std::cout << "SIZE         defines the size of the area in which the game is played." << std::endl;
	std::cout << "OUTSIDECHAR  defines the character used for the perimeter of the game area." << std::endl;
	std::cout << "INSIDECHAR   defines the character used for the inside of the game area." << std::endl;
	std::cout << std::endl;
	std::cout << "--help     display this help and exit" << std::endl;

	std::cout << std::endl;
	std::cout << "OUTSIDECHAR and INSIDECHAR are supposed to be passed as ascii characters" << std::endl;
	std::cout << "but their ascii code must be between 33 and 126." << std::endl;
	std::cout << "Some characters must be escaped like '#' or '*'" << std::endl;

}

void printInviteForHelp()
{
	std::cerr << "Try 'helpMe --help' for more information." << std::endl;

}


struct Parameters
{
    int size = 10;
    char outside = '#';
    char inside = 'o';
};

static unsigned short int
getTerminalColumnsNb()
{
	struct winsize size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return (size.ws_col);
}



bool isSizeArgNumber(char *s)
{
	int curNum = 0;

	while(*s){
		curNum = (*s)-'0';
		if (0<=curNum || curNum>9)
		{
			return 1;
		}
		s++;
	}
	return 0;
}

bool
isOutsideOrInsideChar(char c)
{
	return (c>=33 && c<=126);
}
/*
bool isHelpArg(char *s)
{
	char *helpArg = "--help";
	int argLen = 6; // 6-1 car indexe a 0
	int cursor = 0;
	while(*s && cursor<=argLen){
		if(*s != helpArg[cursor])
		{
			return false;
		}
		s++;
		cursor++;
	}

	if (cursor != argLen)  // On check si on a pas fourni une substring de --help  (5 >> 6-1 car indexe a 0)
	{
		return false;
	}
	return true;
}

*/

const std::string helpFlag= "--help";

bool isAWrongFlag(char *s)
{
	std::string argString = s;
	bool result = ((argString[0]=='-') && (argString[1]=='-') && (argString != helpFlag));
	return result;
}


int parseArgs(int argc, char *argv[], Parameters &params)
{
/*	return meaning:
		0 : one or more args are invalid
		1 : all good
		2 : help wanted
*/
    // RECUPERATION/CHECK DES ARGUMENTS
    // Check si on a demande l'aide
    for(int i = 1; i < argc; i++ ) {
    	if ( std::string(argv[i]) == helpFlag )
    	{
    		printUsage();
    		return 2;
    	}
    }

    if (argc < 3)
    {
		std::cerr << "ERROR! You must specify a square size and a character for the outline\n";
		printInviteForHelp();
		return 0;
    }
    if (argc > 4)
        {
    		std::cerr << "ERROR! You specified too many args\n";
    		printInviteForHelp();
    		return 0;
        }
    for(int i = 1; i < argc; i++ ) {
        if (i==1)
        {
        	// Check si l'argument pour la size represente bien un nombre avant de faire la conversion
        	if (!isSizeArgNumber(argv[i]))
        	{
        		std::cerr << "ERROR! The square size must be a positive number greater than 0\n";
        		std::cerr << "Size specified: " << argv[i] << std::endl;
        		printInviteForHelp();
        		return 0;
        	}

        	// On recupere la size et on error si on a entre un nombre incorrect
        	int size = atoi(argv[i]);

        	int terminalWidth = getTerminalColumnsNb();
        	if(size<1 || size>terminalWidth )
        	{
        		std::cerr << "ERROR! The square size must be set between 1 and " << terminalWidth <<" (terminal size) \n";
            	std::cerr << "Size specified: " << size << std::endl;
            	printInviteForHelp();
            	return 0;
        	}
        	params.size = size;
        }
        if (i==2)
        {
        	if (!isOutsideOrInsideChar(*argv[i]))
        	{
        		std::cerr << "ERROR! The outside char must have ascii code betwen 33 and 126 \n";
            	printInviteForHelp();
            	return 0;
        	}

        	params.outside = *argv[i];

        }
        if (i==3)
        {
        	if (!isOutsideOrInsideChar(*argv[i]))
        	{
        		std::cerr << "ERROR! The inside char must have ascii code betwen 33 and 126 \n";
        		return 0;
        	}
        	params.inside = *argv[i];
        }
    }


	return 1;
}

int main(int argc, char *argv[])
{
//
//	int ww = isAWrongFlag(argv[1]);
//	std::cout << ww << std::endl;
//
//	return 0;

    Parameters snakeParams;
    if (parseArgs(argc, argv, snakeParams) != 1)
    {
    	return 1;
    }

    // int terminalWidth = getTerminalColumnsNb();

    int size     = snakeParams.size;
    char outside = snakeParams.outside;
    char inside  = snakeParams.inside;

    // ON DESSINE LE CARRE

    char toPrint = 0;
    for (int y=0; y<size; y++)
    {
        for (int x=0; x<size; x++)
        {
            toPrint = y>0 && y<size-1 && x>0 && x<size-1 ? inside : outside;
            std::cout << toPrint;
		}

        std::cout << "\n";
    }
    return 0;

}
