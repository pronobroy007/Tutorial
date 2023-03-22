#ifndef SERVER
#define SERVER

#define MAX_CONN 20
#define BUFFER_SIZE 1024 

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

class Server
{
    public:
        int _listen; 

        char* buffer[BUFFER_SIZE];
        
        Server(char* port);
            bool init();
            bool acceptClient();
            void closeConnection();
        ~Server();

    private:
        char* _port;
        struct addrinfo hints;
        struct addrinfo *bind_addr;
};

#endif
