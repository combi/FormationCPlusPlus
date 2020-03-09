#include <iostream>

// YOUR STRUCT HERE
enum myCatCharacter
{
	SAD,
	HUMBLE,
	FREAK,
	ASSHOLE,
	GENEROUS

};

struct Dude {
	char name[8];
    unsigned short age;
	float weight;
	bool isAlive;
	char color[100];

	myCatCharacter character;
};



int 	main()
{

    // YOUR CODE HERE
	Dude charlie = {"Charlie", 3, 2.31, true, "Black", myCatCharacter::GENEROUS};

	/*
	Dude charlie;

	charlie.name[0] = 'C';
	charlie.name[1] = 'h';
	charlie.name[2] = 'a';
	charlie.name[3] = 'r';
	charlie.name[4] = 'l';
	charlie.name[5] = 'i';
	charlie.name[6] = 'e';
	charlie.name[7] = 0;

	charlie.age = 3;
	charlie.weight = 2.31;

	charlie.color[0] = 'B';
	charlie.color[1] = 'l';
	charlie.color[2] = 'a';
	charlie.color[3] = 'c';
	charlie.color[4] = 'k';
	charlie.color[5] = 0;

	charlie.isAlive = true;
	charlie.character = myCatCharacter::GENEROUS;
    */
	std::cout << "My cat name is " << charlie.name << std::endl;
	std::cout << "My cat age is " << charlie.age << std::endl;
	std::cout << "My cat weight is " << charlie.weight << std::endl;
	std::cout << "Do you know if my cat is alive ? " << std::boolalpha << charlie.isAlive << std::endl;
	std::cout << "My cat color is " << charlie.color << std::endl;
	std::cout << "My cat character is " << charlie.character << std::endl;
	if (charlie.character == myCatCharacter::GENEROUS)
		std::cout << "Yes, my cat is awesome." << std::endl;
	else if (charlie.character == myCatCharacter::SAD)
		std::cout << "Oh ..." << std::endl;
	else if (charlie.character == myCatCharacter::HUMBLE)
		std::cout << "This is possible ? Don't believe you." << std::endl;

	return (EXIT_SUCCESS);
}
