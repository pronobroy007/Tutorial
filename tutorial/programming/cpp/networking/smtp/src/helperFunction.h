#ifndef HELPERFUNCTION
#define HELPERFUNCTION

#include <string>
#include <iostream>

class HelperFunction
{
    public:
        HelperFunction(/* args */);
            void parse_url(std::string url, std::string &hostname, std::string &port, std::string &path);
        ~HelperFunction();
};



#endif
