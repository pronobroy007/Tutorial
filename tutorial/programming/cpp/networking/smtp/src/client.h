#ifndef CLIENT
#define CLIENT

#include "header.h"
#define BUFFERSIZE 1024

class Client
{
    public:
        int sock;
        struct addrinfo hints;
        struct addrinfo *bind_addr;

        Client();
            bool connectServer(std::string ip, std::string port);
            void clientClose();
            bool procMsg(std::string msg, char* recvBuffer, int expecting);
            bool sendRequest(const char* msg, int len);
            bool recvResponse(char* msg, int expecting);
        ~Client();

    private:
        SSL_CTX *_ctx;
        SSL *_ssl;

        std::string _ip;
        std::string _port;
        
        int parse_response(char* msg);
};


#endif
