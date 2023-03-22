#include <iostream>
#include <thread>
#include <string>
#include "newClass.h"


int main()
{

	NewClass nc;
	nc.func2;
	std::thread t0(NewClass::func, "This is form another thread .............!");
	std::cout << "hello From main thread ........!" << std::endl;
	//Main program will wait until this thread end.
	t0.join();

	std::thread t1(NewClass::func, "Run this thread separetly from main thread");
	//Main program will not wait for this thread to be finish.
	t1.detach();	

    std::thread t2(&NewClass::fun, std::ref(nc), "Non static function");
    t2.join();


	return 0;
}

