#include <iostream>

struct A { 
	int x; 
	int y; 
};

int main()
{
	int x = 5;
	// Now we take same memory of x and treted as double.
	// To do this we take address of (&x) and make it as a double pointer ((double*)&x)
	// Lastly we derefence it. here first 4 byte is writen by x and another 4 byte is uninitialize.
	double d = *(double*)&x;

	A a = { 100, 200 };
	std::cout << "Access struct normally : " << std::endl;
	std::cout << "a.x : " << a.x << std::endl;
	std::cout << "a.y : " << a.y << std::endl;
	// Here we have a Struct of A and the way we access it using "a.x" or "a.y". 
	// There is another way to access it using type punning.
	// we can treated this struct as array of int by take address of (&a) and make it int pointer((int*)&a)
	// Here arr[0] == a.x and arr[1] == a.y
	int *arr = (int*)&a;
	std::cout << "\nUsing type punning : " << std::endl;
	std::cout << "a.x : " << arr[0] << std::endl;
	std::cout << "a.y : " << arr[1] << std::endl;

	// We also can take address of "a.x" and cast it char pointer
	// Here c[0] == 1st byte of a.x.
	char *c = (char*)&a.x;
	std::cout << "\nConvart a.x ot char pointer : " << std::endl;
	std::cout << c[0] << std::endl;

	// after cast "a.x" into char pointer we can advance 4 byte and again cast it into an int.
	// so now y = a.y.
	int y = *(int*)(c + 4);
	std::cout << "\nAfter Convart a.x ot char pointer, here we convart (a.x+4) to an int : " << std::endl;
	std::cout << "a.y : " << y << std::endl;
	
	return 0;
}









