#include <iostream>

void printHello(std::string str)
{
    std::cout << str << std::endl;
}

bool checkEqual(int a, int b)
{
    if(a == b) return true;
    else return false;
}

bool checkGrather(int a, int b)
{
    if(a > b) return true;
    else return false;
}

void someFunction(int a, int b, bool(*function)(int, int))
{
    if(function(a,b))
        std::cout << "Pass condition" << std::endl;
    else
        std::cout << "faild condition" << std::endl;
}

int main()
{
    void(*function)(std::string) = printHello;
    function("Hello World");


    int a = 4, b = 3;
    someFunction(a, b, [](int a, int b)->bool { if(a>b)return true; else return false; });
    someFunction(a, b, [](int a, int b)->bool { if(a==b)return true; else return false; });

    return 0;
}
