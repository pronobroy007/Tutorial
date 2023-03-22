#include <vector>
#include <string>
#include <iostream>

// 1st void* for int type.
// 2nd void* for char type.
// 3rd void* for std::vector<std::string> type.
void print(void*, void*, void*);

int main()
{
	void *data;

	//We can assaign anything into void pointer. This is similler to type_Punning.
    //But we can't read or write data in a void pointer for this we need to cast this
    //pointer to any data type. Assaign an integer into void pointer.
	std::cout << "........................................." << std::endl;
	int x = 5;
	data = (void*)&x;
	// Now x = 10;
	*(int*)data = 10;
	std::cout << "Assaign an integer into void pointer and modify 5 to 10 " << std::endl;
	std::cout << "void pointer : " << *(int*)data << std::endl;
	std::cout << "int x : " << x << std::endl;
	std::cout << "........................................." << std::endl;



	//Assaign an char into void pointer.
	char c = '5';
	data = (void*)&c;
	// Now *ch and c have same memory address
	char *ch = (char*)data;
	*ch = 'h';
	std::cout << "Assaign an char into void pointer and modify 5 to h: " << std::endl;
	std::cout << "void pointer : " << *(char*)data << std::endl;
	std::cout << "char c : " << c << std::endl;
	std::cout << "........................................." << std::endl;



	//Assaign an vector into void pointer.
	std::vector<std::string> str;
	str.push_back(std::string("Hello"));
	data = (void*)&str;
	// Now str and *st have same vector
	std::vector<std::string> *st = (std::vector<std::string> *)data;
	st->push_back(std::string("world"));
	//Now print str.....
	std::cout << "Assaign an vector into void pointer " << std::endl;
	std::cout << "Print str which we define avobe " << std::endl;
	for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); it++)
		std::cout << *it << std::endl;
	std::cout << "........................................." << std::endl;


	// Calling print function
	print((void*)&x, (void*)&c, (void*)&str);

	// We modify str in print function and it dosen't effect here because we don't 
	// create a pointer of vector<string> in print function.
	std::cout << "........................................." << std::endl;
	for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); it++)
		std::cout << *it << std::endl;
	std::cout << "........................................." << std::endl;

	return 0;
}


void print(void* i, void *c, void* v)
{
	//Here we convart void* into an integer........
	std::cout << "........................................." << std::endl;
	std::cout << "From Print() : " << std::endl;
	int *x = (int*)i;
	std::cout << "Here we cast a void* to int* : ";
	std::cout << *x << std::endl;

	//Here we convart void* into an char ........
	char ch = *(char*)c;
	std::cout << "Here we cast a void* to char : ";
	std::cout << ch << std::endl;

	//Here we convart void* into an vector ........
	std::vector<std::string> str = *(std::vector<std::string> *) v;
	std::cout << "Here we cast a void* to vector<string> : ";
	str.push_back(std::string("void Pointer"));
	std::cout << str[str.size()-1] << std::endl;
	std::cout << "........................................." << std::endl;
	std::cout << std::endl;
}















