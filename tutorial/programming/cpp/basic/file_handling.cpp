#include <iostream>
#include <fstream>

int main()
{
	int size = 1024;
	char buffer[size];

	std::ifstream input;
	/************************************************************************************** 
	Default Open Modes :
		ifstream 	ios::in
		ofstream 	ios::out
		fstream 	ios::in | ios::out 

	This function take mode as second argument.
	ios::binary 	reading file as binary mode
	ios::ate 	 Set the initial position at the end of the file.
	ios::app 	 All output operations are performed at the end of the file,

	input.open("string.cpp", std::ios::binary | std::ios::ate);
	or
	std::ifstream input("string.cpp", std::ios::binary | std::ios::ate);

	ios::in	Open for input operations.
	ios::out	Open for output operations.
	This tow mode is used for fstream.
	**************************************************************************************/
	input.open("string.cpp", std::ios::binary);
	if(!input.is_open())
		std::cout << "Not opened" << std::endl;


	/************************************************************************************** 
	tellg() for input file and tellp() for output file
	----------------------------------------------------
        These two member functions with no parameters return a value of the member 
        type streampos, which is a type representing the current get position 
        (in the case of tellg) or the put position (in the case of tellp).

	seekg() for input file and seekp() for output file
	------------------------------------------------------
        These functions allow to change the location of the get and put positions. 
        Both functions are overloaded with two different prototypes. The first form is:
	**************************************************************************************/
	//Get file size.
	input.seekg(0, std::ios::end);
	int file_size = input.tellg();
	//Make input pointer to the begining
	input.seekg(0, std::ios::beg);
	std::cout << "Total file size : " << file_size << std::endl;

	//Reading line by lline
	/* 
	std::string line;
	while(getline(input, line))
		std::cout << line << std::endl;
	*/

	/*
	while(!input.eof())
	{
		input >> buffer;
		std::cout << buffer << std::endl;
	}
	*/

	//Reading a block of memory from file.
	input.read(buffer, size);
	std::cout << buffer << std::endl;

	//Close file.
	input.close();


	/****************************************************************/
	/************************** READING FILE ************************/
	//To write text starting from last use ios::app mode
	//Here if "example.text" not exist then it create first then start writing
	/* 
	std::ofstream output ("example.txt");
	if (output.is_open())
	{
		output << "This is a line.\n";
		output << "This is another line.\n";
		output.close();
	}
	else std::cout << "Unable to open file";
	output.close();
	*/
	return 0;
}
