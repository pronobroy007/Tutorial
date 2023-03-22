#include "server.h"

Server::Server(char* port)
{
    _port = port;
    //Initialize the OpenSSL library. 
    SSL_library_init();
    //To causes OpenSSL to load all available algorithms. Alternately, 
    //you could load only the algorithms you know are needed. For our 
    //purposes, it is easy to load them all. 
    OpenSSL_add_all_algorithms();
    //causes OpenSSL to load error messages when something goes wrong
    SSL_load_error_strings();

    bzero(&hints, sizeof(hints));
}

bool Server::init()
{
	//This is for Broke Pipe exception handler for sending to a client which is close.
	signal(SIGPIPE, SIG_IGN);
    /*
    * You can think of this object as a sort of factory for SSL/TLS connections. 
    * It holds the initial settings that you want to use for your connections. 
    * Most programs only need to create one SSL_CTX object, and they can reuse it for all their connections.
    * 
    * We use TLS_client_method(), which indicates that we want general-purpose, 
    * version-flexible TLS methods available. Our client automatically negotiates 
    * the best mutually supported algorithm with the server upon connecting.
    */
    _ctx = SSL_CTX_new(TLS_server_method());
    if(!_ctx)
    {
        perror("Faiels SSL_CTX_new()");
        return false;
    }

    /*
    * we can set it to use our self-signed certificate and key.
    */
    if (!SSL_CTX_use_certificate_file(_ctx, "cert.pem" , SSL_FILETYPE_PEM)
    || !SSL_CTX_use_PrivateKey_file(_ctx, "key.pem", SSL_FILETYPE_PEM)) {
        fprintf(stderr, "SSL_CTX_use_certificate_file() failed.\n");
        ERR_print_errors_fp(stderr);
        return false;
    }


    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    //ai_flags = AI_PASSIVE is set. This is telling getaddrinfo() that we want it to bind to 
    //the wildcard address. That is, we are asking getaddrinfo() to set up the 
    //address, so we listen on any available network interface.
    hints.ai_flags = AI_PASSIVE;
    //This function will fill in a struct addrinfo structure with the needed information.
    getaddrinfo(0, _port, &hints, &bind_addr);

    // Creating socket file descriptor 
    if ((_listen = socket(bind_addr->ai_family, bind_addr->ai_socktype, bind_addr->ai_protocol)) == 0) 
    { 
        perror("socket failed"); 
        return false;
    } 
       
    //if (bind(_listen, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0 ) 
    if (bind(_listen, bind_addr->ai_addr, bind_addr->ai_addrlen) < 0 ) 
    { 
        perror("bind failed"); 
        return false;
    } 
    freeaddrinfo(bind_addr);

    if (listen(_listen, MAX_CONN) < 0) 
    { 
        perror("listen"); 
        return false;
    } 


    
    return true;
}


bool Server::acceptClient()
{
    //Client_info c;
    Client_info c;
    c.size = sizeof(c.client_addr);
    c.socket = accept(_listen,(struct sockaddr*) &c.client_addr, &c.size);
    if (!c.socket) 
    {
        perror("Faield to accept client");
        return false;
    }


    /*
    * Make TLS cnnection :
    *##################### 
    * 
    * SSL_new() is used to create an SSL object. This object is used 
    * to track the new SSL/TLS connection.
    */
    c.ssl = SSL_new(_ctx);
    if(!_ctx)
    {
        std::cout << "SSL_new() faield" << std::endl;
        return false;
    }
    /*
    * The SSL object is then linked to our open TCP socket using SSL_set_fd().
    * The SSL_accept() function is called to establish the TLS/SSL connection. 
    */
    SSL_set_fd(c.ssl, c.socket);
    if (SSL_accept(c.ssl) != 1) {
        fprintf(stderr, "SSL_accept() failed.\n");
        ERR_print_errors_fp(stderr);
        return 1;
    }

    _client_info_vec.push_back(c);
    printf ("SSL connection using %s\n", SSL_get_cipher(c.ssl));
    std::cout << "Wellcome to Serverproc ...!" << std::endl; 

    //std::cout << "Connected : " << get_client_address(c.size() - 1) << std::endl << std::endl;
    return true;
}

bool Server::recvRequest(int index, char* msg, int len)
{
    int p = 0;
    char *ptr = (char*)msg;
    while (true)
    {
        int byte_recv = SSL_read(_client_info_vec[index].ssl, ptr + p, len - p);
        std::cout << "Recv byte : " << byte_recv << std::endl;
        if(byte_recv < 1)
        {
            msg[p] = 0;
            send400(index);
            break;
        }

        char *q = strstr(msg, "\r\n\r\n");
        if(q)
        {
            std::cout << "Request : " << std::endl;
            std::cout << "---------" << std::endl;
            std::cout << msg << std::endl;
            std::cout << "****************************************" << std::endl;

            if(strncmp("GET /", msg, 5) == 0)
            {
                char* path = msg + 4;
                char* end = strstr(path, " ");
                if(!end)
                    send400(index);
                else
                    *end = 0;                

                std::cout << "Path : " << path << std::endl;
                server_response(index, path);
            }else
                send400(index);

            break;
        }

        p += byte_recv;
    } 

    return true;
}


void Server::closeConnection()
{
    close(_listen);
    //SSL_shutdown(ssl);
    //SSL_free(ssl);
    SSL_CTX_free(_ctx);
}

Server::~Server(){}


