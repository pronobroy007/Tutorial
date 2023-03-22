#ifndef HELPERFUNCTION
#define HELPERFUNCTION

#include "connection.h"
#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <map>
#include <vector>

class HelperFunction
{
public:
    HelperFunction(/* args */);
        bool parse(std::string src, char delemeter, std::vector<std::string> &buffer);
        bool parse(std::string src, std::vector<std::vector<std::string>> &buffer);
        void sort(std::vector<std::string> &data);
    ~HelperFunction();

private:
    int sock;
};


#endif