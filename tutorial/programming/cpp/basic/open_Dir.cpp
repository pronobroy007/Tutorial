#include <iostream>

#include <sys/types.h>
#include <dirent.h>

int main(int argc, char** argv)
{
    DIR *dir;
    struct dirent *rd;

    dir = opendir(".");
    if(!dir)
    {
        std::cout << "Error to open directory" << std::endl;
        return 0;
    }

    while((rd=readdir(dir)) != NULL)
        std::cout << rd->d_name << std::endl;

    return 0;
}
