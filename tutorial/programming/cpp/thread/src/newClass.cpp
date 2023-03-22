#include "newClass.h"

NewClass::NewClass(/* args */)
{
}

bool NewClass::fun(std::string msg)
{
    std::lock_guard<std::mutex> lock(mu);
    std::cout << msg << std::endl;
    return false;
}

void NewClass::func(std::string msg)
{
    int i = 0;
    while(i < 1000)
    {
        func2();
        i++; 
    }

    std::cout << msg << std::endl;
}

void NewClass::func2()
{
    int i;
    i++;
}

NewClass::~ NewClass()
{

}
