#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <string.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <fstream>

#include "helperFunction.h"

class Client : public HelperFunction
{
    public:
        int sock;
        struct addrinfo hints;
        struct addrinfo *bind_addr;

        Client();
            bool connectServer(std::string url, std::string port);
            void clientClose();
            void send_req();
            bool recvResponse();
        ~Client();

    private:
        SSL_CTX *_ctx;
        SSL *_ssl;

        std::string _ip;
        std::string _hostname;
        std::string _path;
        std::string _port;
};


#endif
