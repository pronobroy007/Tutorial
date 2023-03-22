#ifndef SERVER
#define SERVER

#define MAX_CONN 20
#define BUFFER_SIZE 1024 

#include "connection.h"

class Server : public Connection
{
    public:
        fd_set master;
        int max_sock;
        int _listen; 

        char* buffer[BUFFER_SIZE];
        
        Server(char* port);
            bool init();
            bool acceptClient();
            void closeConnection();
        ~Server();
};

#endif
