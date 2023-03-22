#ifndef CONNECTION
#define CONNECTION

#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <string.h>
#include <map>
#include <vector>
#include <unistd.h>

struct SOCK_OPT
{
    std::string name = "Broadcast";
    int level = SOL_SOCKET;
    int optName = SO_BROADCAST; 

    SOCK_OPT(std::string n, int l, int on)
    {
        name = n;
        level = l;
        optName = on;
    }
};


class Connection
{
    public:
        Connection();
            //Function........
            bool send_all(int sock, char* buffer, int len);
            bool recv_all(int sock, char* buffer, int len);
        ~Connection();

    protected:
        char* _ip;
        char* _port;

        struct addrinfo hints;
        struct addrinfo *bind_addr;
};


#endif
