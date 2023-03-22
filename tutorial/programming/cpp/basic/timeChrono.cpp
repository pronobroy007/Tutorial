#include <iostream>
#include <chrono>
#include <unistd.h>
#include <cmath>

using namespace std::chrono;
int main()
{
    /*
    * Clock :
    * std::chrono::system_clock             //current time according to time system - is not stady
    * std::chrono::steady_clock             //gose at uniform rate - is stady
    * std::chrono::high_resolution_clock    //provide smallest possible time period
    *
    *
    *
    * Duration :
    * std::chrono::duration<>                                   //represents time duration
    * std::chrono::duration<int, std::ratio<1,1>>               //number of seconds stored in "int"
    * std::chrono::duration<int, std::ratio<60,1>>              //number of minuts stored in "int"
    *
    * microseconds mi(2700);
    * nanoseconds ns = mi;                                      //2700000 nanoseconds.
    * milliseconds mil = duration_cast<milliseconds>(mi);       //2 milliseconds
    *
    *
    *
    * Time Point :
    * time_point<>                                //represents a point of time 
    * time_point<system_clock, milliseconds>      //represents a point of time in milliseconds
    */
    steady_clock::time_point start = steady_clock::now();
    std::cout << "Current Time in Steady Clock : " << start.time_since_epoch().count() << std::endl;
    while (true) 
    {
        steady_clock::time_point end = steady_clock::now();
        duration<double> d = end - start;
        double millSec = duration_cast<milliseconds>(d).count();
        int sec = millSec / 1000;

        if(start == steady_clock::time_point())
            std::cout << "Not Set" << std::endl;
        else
            std::cout << "Set" << std::endl;

        std::cout << int(sec / 3600) % 24
            << ":" << int(sec / 60) % 60
            << ":" << std::fmod(sec, 60) 
            << ":" << std::fmod(millSec, 1000) << std::endl;

        sleep(3);
    }

    return 0;
}



