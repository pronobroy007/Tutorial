#ifndef NEWCLASS 
#define NEWCLASS
#include <iostream>
#include <string>
#include <mutex>


class NewClass
{
public:
    mutable std::mutex mu;

    NewClass(/* args */);
        bool fun(std::string msg);
        static void func(std::string msg);
        static void func2();
    ~NewClass();
};

#endif
