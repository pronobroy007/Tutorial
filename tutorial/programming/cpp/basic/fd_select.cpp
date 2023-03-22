#include <iostream>
#include <string.h>
#include <unistd.h>


int main()
{
    int maxfd;
    int stdIN = 0;
    fd_set reads;
    struct timeval timeout;


    while (true)
    {
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        FD_ZERO(&reads);
        FD_SET(stdIN, &reads);
        maxfd = 1;

        int sret = select(maxfd + 1, &reads, NULL, NULL, &timeout);

        if(sret == 0)
        {
            std::cout << "Time out occer" << std::endl;
            break;
        }
        else if(FD_ISSET(stdIN, &reads))
        {
            //Reading from stander input.
            char buff[50];
            bzero(buff, 50);
            read(stdIN, buff, 50);
            std::cout << buff << std::endl;
        }


    }


    return 0;
}
