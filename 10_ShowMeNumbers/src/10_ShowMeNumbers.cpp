#include <iostream>
#include <iomanip>

void printMeNumbers(int number)
{
	if (number > 0)
	{
		std::cout << "\[";
		for(int i=0; i<number; i++)
		{
			std::cout << i;
			if (i < number-1)
			{
				std::cout << " ";
			}
		}
		std::cout << "]" << std::endl;
	}

	return;
}


void printNumbersRecurseUntil(int i, int max)
{
	 if(i<max)
	 {
		std::cout << i;
		if (i < max-1)
		{
			std::cout << " ";
		}
		printNumbersRecurseUntil(++i, max);
	 }
}

void printNumbersRecurseUntil(float i, float max)
{
	 if(i<max)
	 {
		std::cout << i;
		if (i < max-0.1)
		{
			std::cout << " ";
		}
		i = i+0.1;
		printNumbersRecurseUntil(i, max);
	 }
}

void printNumbersRecurse(int number)
{
	std::cout << "version int" << std::endl;
	if (number > 0)
	{
		std::cout << "\[";
		printNumbersRecurseUntil(0, number);
		std::cout << "]" << std::endl;
	}

	return;
}


void printNumbersRecurse(float number)
{
	std::cout << "version float" << std::endl;
	if (number > 0.0)
	{
		std::cout << "\[";
		printNumbersRecurseUntil(0.0, number);
		std::cout << "]" << std::endl;
	}

	return;
}




int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cerr << "No numbers given in parameter." << std::endl;
		return (EXIT_FAILURE);
	}

	int intToPrint = 0;
	float floatToPrint = 0.0;

	if (argc == 4)
	{
		std::cout << "A" << std::endl;

		if ( std::string("--decimals") == std::string(argv[1]) )
		{
			std::cout << "decimals wanted." << std::endl;
			int numDecimals = std::stoi(argv[2]);
			std::cout << std::fixed;
			std::cout << std::setprecision(numDecimals);
		}
	}
	else{
		std::cout << "B" << std::endl;
	}


	if (std::string(argv[argc-1]).find(".") != std::string::npos)
	{
		std::cout << "detected float" << std::endl;
		floatToPrint = std::stof(argv[argc-1]);
		printNumbersRecurse(floatToPrint);
	}
	else
	{
		std::cout << "detected int" << std::endl;
		intToPrint = std::stoi(argv[argc-1]);
		printNumbersRecurse(intToPrint);
	}


	return (EXIT_SUCCESS);
}
