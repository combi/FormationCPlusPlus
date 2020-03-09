#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

static unsigned short int
getTerminalColumnsNb()
{
	struct winsize size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return (size.ws_col);
}

/*
int checkSizeArg(const char *s)
{
  if(*s == '-'){
    return -1;
  }
  int num=0;
  while(*s){
    num=((*s)-'0')+num*10;
    s++;
  }

  if (num > getTerminalColumnsNb())
  {
	  return -2;
  }
  return num;
}
*/


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

int main(int argc, char *argv[]) {

	if (false)
	{
		printf( "=====================================================\n" );
		printf("Drawing a square\n");

		printf( "argc = %d\n", argc );
		for( int i = 0; i < argc; i++ ) {
			printf( "argv[%d] = %s\n", i, argv[i]);
		}

		printf( "-----------------------------------------------------\n" );
	}
    // DEFAULT VALUES

    int size = 1;
    char outside = '#';
    char inside = 'o';

    int terminalWidth = getTerminalColumnsNb();


    // RECUPERATION/CHECK DES ARGUMENTS
    // Check si on a demande l'aide
    for(int i = 1; i < argc; i++ ) {
    	if (isHelpArg(argv[i]))
    	{
    		std::cout << "\n";
    		std::cout << "Usage: j'ai pas encore trouve comment printer des grands blocs de texte\n";
    		return 0;
    	}
    }


    if (argc< 3)
    {
		std::cerr << "ERROR! You must specify the square size and a character for the outline\n";
		return 1;

    }

    for(int i = 1; i < argc; i++ ) {
        if (i==1)
        {
        	// Check si l'argument pour la size represente bien un nombre avant de faire la conversion
        	if (!isSizeArgNumber(argv[i]))
        	{
        		std::cerr << "ERROR! The square size must be a positive number greater than 0\n";
        		printf("Size specified: %s\n", argv[i]);
        		return 1;
        	}

        	// On recupere la size et on error si on a entre un nombre incorrect
        	size = atoi(argv[i]);

        	if(size<1 || size>terminalWidth)
        	{
        		std::cerr << "ERROR! The square size must be set between 1 and " << terminalWidth <<" (terminal size) \n";
            	printf("Size specified: %d\n", size);
        		return 1;
        	}
        }
        if (i==2)
        {
        	outside = *argv[i];

        	if (!isOutsideOrInsideChar(outside))
        	{
        		std::cerr << "ERROR! The outside char must have ascii code betwen 33 and 126 \n";
        	}



        }
        if (i==3)
        {
        	inside = *argv[i];

        	if (!isOutsideOrInsideChar(inside))
        	{
        		std::cerr << "ERROR! The inside char must have ascii code betwen 33 and 126 \n";
        	}
        }
    }


    // FEEDBACK

    printf("Will draw a square:\n");
    printf("Dimension    : %d\n", size);
    printf("Outside char : %c\n", outside);
    printf("Inside char  : %c\n", inside);



    printf( "-----------------------------------------------------\n" );
    printf( "\n" );

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





/* BUG 1
=====================================================
./drawMeASquare 10 * . (avec une etoile pour l'outside)

dddddddddd
d........d
d........d
d........d
d........d
d........d
d........d
d........d
d........d
dddddddddd

 */


/* BUG 2
=====================================================
./drawMeASquare 10 # .
ERROR! You must specify the square size and a character for the outline
*/

/*
 * https://stackoverflow.com/questions/13145777/c-char-to-int-conversion
 *
 *
 * Je peux faire atoi directement, mais je dois faire std::stoi.
 * Je ne saisis pas trop pourquoi.
 * stoi est dans basicString, mais je n'ai pas inclus basicString.h
 * Je me suis demande si stdlib.h faisait un include qui "amene" stoi dans le namespace de stdlib, mais je n'ai pas trouve
 * atoi est dans stdlib.h et j'ai vu ca:
 * using std::atoi;
 * Je suppose que le using, signifie que
 *
 * */
