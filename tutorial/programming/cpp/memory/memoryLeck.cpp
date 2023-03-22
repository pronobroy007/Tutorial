#include <iostream>



//####################################################################################
//				Fix all memory error
//####################################################################################
/*
   This function will give flowing error in vlgrind
   Invalid write of size 4
   at which address and which line of code also which function it occer
   by which function call this function
	
   Invalid read of size 4
   at which address and which line of code also which function it occer
   by which function call this function
	
   alos give more address information for this memory leck.

   Heap Summery
   -------------
   		This will give information about how many byte allocate but program don't deallocate.

		in use at exit = how many byte allocated
		total heap usage = how many byte actually use, how many memory get free
*/
void test1()
{
	int* mem = new int;
	for (int i = 0; i < 3; i++)
		{
			mem[i] = i;
			std::cout << mem[i] << std::endl;
		}
	
}



//####################################################################################
/*	This function will give flowing error in vlgrind
	Invalid write of size 4
	==12654==    at 0x109227: test() (memorytest2.cpp:60)
	==12654==    by 0x10918D: main (memorytest2.cpp:8)
	==12654==  Address 0x4d5dc80 is 0 bytes inside a block of size 12 free'd

	Here it say we have an invalid write operation. 
	in test() function and line 60 and this function calling by main() function
	and also say that we are writing an address which is "free'd"	
*/
void test2()
{
	int* mem = new int[3];
	for (int i = 0; i < 3; i++)
		{
			mem[i] = i;
			std::cout << mem[i] << std::endl;
		}
	delete [] mem;
	mem[0] = 9;
	
}




//####################################################################################
/*	
   This function will give flowing error in vlgrind

	==13385== Conditional jump or move depends on uninitialised value(s)
	==13385==    at 0x4838C65: strlen (vg_replace_strmem.c:460)
	==13385==    by 0x4BD79EE: vfprintf (vfprintf.c:1638)
	==13385==    by 0x4BDE605: printf (printf.c:33)
	==13385==    by 0x109181: test() (memorytest3.cpp:91)
	==13385==    by 0x10915D: main (memorytest3.cpp:10)
	
	Here this error say that we are reading uninitialised value.
   	main() function call test() function and in test() function we have error in line 91. 
*/
char* getstring()
{
	char mess[] = "hello world";
	char* ret = mess;
	return ret;
}


void test3()
{
	printf("String : %s\n", getstring());
}




//************************************************************************
int main()
{
	test1();
	test2();
	test3();
}






