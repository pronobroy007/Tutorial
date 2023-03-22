#ifndef CLIENT
#define CLIENT

#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <unistd.h>"

class Client 
{
    public:
        int sock;
        struct addrinfo hints;
        struct addrinfo *bind_addr;

        Client();
            bool init();
            void clientClose();
        ~Client();

    private:
        char* _ip;
        char* _port;
};


#endif
