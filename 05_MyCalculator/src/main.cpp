#include <iostream>
// #include <cstdlib>

int main()
{
	int	number1 = 10;
	int	number2 = 11;
	int	result = 0;
	char usedOperator = '%';


	if (usedOperator == '+')
	{
		result = number1 + number2;
	}
	else if (usedOperator == '-')
	{
		result = number1 - number2;
	}
	else if (usedOperator == '*')
	{
		result = number1 * number2;
	}
	else if (usedOperator == '/')
	{
		result = number1 / number2;
	}
	else if (usedOperator == '%')
	{
		result = number1 % number2;
	}

	std::cout << number1 << ' ' << usedOperator << ' ' << number2 << " = " << result << std::endl;
	return (0);
}
