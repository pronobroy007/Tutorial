#ifndef CLIENTMANAGER  
#define CLIENTMANAGER 

#include "headerFile.h"

#define BUFFER 1024

struct Client_info{
    SSL *ssl;
    int socket;
    struct sockaddr_storage client_addr;
    socklen_t size;
    char request[BUFFER];
};

class ClientManager
{
    public:
        ClientManager();
            //Insert Client_info struct and Return socket.
            int get_client(fd_set &reads);
            //Close an established connection and remove from Client_info struct.
            bool drop_client(int index);
            //Return client IP.
            std::string get_client_address(int index);
            //Return 
            fd_set wait_on_client(int server);
            //Send response to client and drop connection.
            void server_response(int index, char* path);
            void send_all(SSL* ssl, char* msg, int len);

            //Error handiling
            //Bad request and drop client.
            void send400(int index);
            //Unknown file request and drop client.
            void send404(int index);
            void print();
            std::string get_content_type(const char* path);
        ~ClientManager();

    protected:
       std::vector<Client_info> _client_info_vec; 
       char response[BUFFER];
};

#endif