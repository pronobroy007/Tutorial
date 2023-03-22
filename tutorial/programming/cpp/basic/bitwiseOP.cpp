#include <iostream>


//8192  4096  2048  1024   512	 256  128	64	32	16	8	4	2	1



int main()
{
	//And Operation  :
	//------------------
	//	 5(0101)	 
	//	 9(1001)   
	//	---------
	//	 1(0001)
	std::cout << "And Operation : " << (5 & 9) << std::endl;

	//Here we check if first bit of 'value' is 1 or 0
	char value = 0xDA;
	//0xDA = 1101 1010	and 	0x80 = 1000 0000
	if((value & 0x80) == 0x00)
		std::cout << "First bit of 'value' is set 0" << std::endl;
	else 
		std::cout << "First bit of 'value' is set 1" << std::endl;

	//This is better way to do thes Using this we can check multiple bit
	//what is value of  3-6(0011-1100) bit of 0xDA = 1101-1010
	int k = (value & 0x3C) >> 2;
	std::cout << "Value of 3 to 6 bit : " << k << std::endl;
	std::cout << std::endl;
	

	

	//OR Operation :
	//--------------
	//	 5(0101)	 
	//	 9(1001)  
	//	---------
	//	13(1101)
	std::cout << "OR Operation : " << (5 | 9) << std::endl;
	std::cout << std::endl;


	//XOR Operation (ODD 1 Dictector):
	//--------------------------------
	//	 5(0101) 
	//	---------
	//	 9(1001)   
	//	 13(1101)
	std::cout << "XOR Operation : " << (5 ^ 9) << std::endl;
	std::cout << std::endl;


	//LEFT SHIFT :
	//------------
	//9 is an integer it mean it 4 byte long So its binary is 
	//00000000 00000000 00000000 00001001	=	9  as an int.
	//Now if we left shift of it's bit 3 time's then result is 
	//00000000 00000000 00000000 01001000 	=  64 + 8 = 72
	std::cout << "LEFT SHIFT Operation : " << (9 << 3) << std::endl;
	std::cout << std::endl;


	return 0;
}











