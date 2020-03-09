#include <iostream>
#include <cstdlib>

int main()
{
	char result[] = {
			'c','o','m','b','i','\n',
			'd','o','r','i','a','n', '\n',
			'b','l','u','e', '\n',
			't','h','o','m','a','s', '\n',
			'e','m','e','r','i','c', '\n',
			's','t','e','p','h','a','n','e', '\n'
		};

	// std::cout << "What a beautiful Hello world !" << std::endl;
	// std::cout << result[0] << std::endl;
	int numItems = sizeof(result);
	for (int i=0; i < numItems; i++) {
		std::cout << result[i];
	}
	std::cout << std::endl;


	return (EXIT_SUCCESS);
}
