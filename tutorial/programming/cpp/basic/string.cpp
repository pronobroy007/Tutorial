#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

void C_STYL();

int main()
{
	//String constructor.
    //----------------------
        std::string s1("Hello");				//S1 = Hello.         
        std::string s2("hello", 3);				//s2 = hel 
        std::string s3(s1, 2);					//s3 = llo  copy from 2 to end.
        std::string s4(s1, 2, 2);				//s4 = ll   
        std::string s5(5, 'a');					//s5 = aaaaa
        std::string s6({'a', 'b', 'c'});		//s6 = abc

	//String operations 
    //----------------------
        s1 = "GoodBye";
        s1.resize(9);			//Here size if 9
        s1.resize(3);			//Here size if 3  and s1 = Goo

        //Push and Pop
        s1.push_back('x');		//s1 = Goox.
        s1.pop_back();			//s1 = Goo.

        //Assign ............
        s2 = "GoodBye";
        s1.assign(s2);					//s1 = s2 (GoodBye).
        s1.assign(s2, 2, 4);			//s1 = odBy
        s1.assign({'a', 'b', 'c'});		//s1 = abc

        s1.append(" def");				//s1 = abc def
        s1.insert(3, "GoodBye", 4);		//s1 = abcGood def
        s1.erase(3, 4);					//s1 = abc def
        s1.substr(4, 3);				//return "def"
        s1.replace(1, 1, "world");       //s1 = "dworldf"


    //Find operations
    //------------------
        //Find function fo string.
        s2 = "Http://www.example.com:80/res/page1.php?user=bob#account";
        //Here p = 1st occurrence of "://"
        ssize_t p = s2.find("://");
        //Here p2 = 2nd occurrence of "://"
        ssize_t p2 = s2.find("://", p+1);
        s1.assign(s2, p+3, s2.size());
        std::cout << "Find : " << s1 << std::endl;

        //Find from end of file.
        p = s2.rfind("bob");

	//Copy String to char
    //----------------------
        s1 = "GoodBye";
        char value[100];
        s1.copy(value, s1.size());		//value = "GoodBye"

	//convert string to int
    //----------------------
		std::cout << std::endl;
		std::string integer = "100";
		int _int = stoi(integer);
		std::cout << "Int value : " << _int << std::endl;

		//C++ Way...............
		integer = "2530";
		std::stringstream ss(integer);	
		ss >> _int;
		std::cout << "Int value c++ way : " << _int << std::endl;

        //Hex string to decemal
		integer = "bb3";
        std::stringstream s0(integer);	
		s0 >> std::hex >> _int;
		std::cout << "Hex " << integer << " strint to Int : " << _int << std::endl;


	//Convert int to string 
    //----------------------
        _int = 15234;
        integer = std::to_string(_int);
        std::cout << "String value : " << integer << std::endl;
        std::cout << std::endl;




	std::string str = "hello";
	s1.insert(3, str.c_str(), str.size());	
	std::cout << s1 << std::endl;
	std::cout << "Size : " << s1.size() << std::endl;

	//For c style string..
	std::cout << std::endl;
	std::cout << "C STYLE string : " << std::endl;
	std::cout << "-----------------" << std::endl;
	C_STYL();
	return 0;
}


void C_STYL()
{
	char str[300] = "GET /smile.png HTTP/1.1 Host: 127.0.0.1:5555"
				"Accept-Language: en-US,en;q=0.5"
				"Accept-Encoding: gzip, deflate";

	char str1[] = "Referer: http://127.0.0.1:5555/page2.html"
				"Cookie: hblid=d68d9oPZlLpTTofZ3m39N0J0BoO012Gy; olfsk=olfsk8622875609877502"
				"Connection: keep-alive";

	std::cout << "Length of first string : " << strlen(str) << std::endl;
	
	/**************************************
	 * strcat() :
	 * ----------
	 * 		Here strcat() will add two string.	
	 * 
	 * strncat() :
	 * -----------
	 *		Here strncat() will concatinate 10 charecters only.
	 *		strncat(str, str1, 10);
	 * 
	 **************************************/
	strcat(str, str1);
	std::cout << "Length of first string after concatenate : " << strlen(str) << std::endl;

	/**************************************
	 * strcpy()
	 * --------
	 * 		coyp into string or array of chrecter.
	 **************************************/
	strcpy(str, "Hello");
	strcpy(str1, "Helld");

	/**************************************
	 * strcmp()
	 * --------
	 * 		Compair two string charecter by charecter.
	 * 		0		=	Both string are equal.
	 * 		+ num	=	first unmatch charecter less then second one
	 * 		- num	=	first unmatch charecter grather then second one
	 * 
	 * strncmp(char* str1, char* str2, ssize_t n) :
	 * ----------------------------------------------
	 * 		Compair two string charecter by charecter at most first n bytes.
	 *		strncmp(str, str1, 4); 
	 *
	 **************************************/
	std::cout << "Compair two string : " << strcmp(str, str1) << std::endl;
	std::cout << "Compair two string : " << strncmp(str, str1, 4) << std::endl;


	/**************************************
	 * strstr() :
	 * -----------
	 * 		Find first occurrence of s2 in s1 and 
	 * 		return pointer where first occurrence occer.
	 * 
	 **************************************/
	strcpy(str, "Hello, how are you");
	//Here 	p = "are you"
	char *p = strstr(str, "are");
	std::cout << "strstr() : " << p << std::endl;

/* 
 if(strncmp("GET /", client->request, 5)) {
			send_400(client);
			} else {
				char *path = client->request + 4;
				char *end_path = strstr(path, " ");
				if (!end_path) {
					send_400(client);
				} else {
					*end_path = 0;
					serve_resource(client, path);
				}
			}
*/
	
}
