#include <iostream>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		std::cout << "Password Chaking ... ... " << std::endl;
		if (strcmp(argv[1], "aaaa-bbbb-cccc-dddd") == 0)
			std::cout << "Password correct!" << std::endl;
		else
			std::cout << "Password wrong!" << std::endl;
	}	
	else
		std::cout << "Use Password in CLA" << std::endl;

	return 0;
		
}
