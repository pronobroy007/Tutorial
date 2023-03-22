#include "server.h"

Server::Server(char* port)
{
    _port = port;

    bzero(&hints, sizeof(hints));
}

bool Server::init()
{
	//This is for Broke Pipe exception handler for sending to a client which is close.
	signal(SIGPIPE, SIG_IGN);

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

    //Set fd_set for select().
    FD_ZERO(&master);
    FD_SET(_listen, &master);
    max_sock = _listen;

    std::cout << "Wellcome to Serverproc ...!" << std::endl; 
    return true;
}


bool Server::acceptClient()
{
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    int socket_client = accept(_listen,(struct sockaddr*) &client_address, &client_len);
    if (!socket_client) 
    {
        perror("Faield to accept client");
        return false;
    }

    FD_SET(socket_client, &master);
    if (socket_client > max_sock)
        max_sock = socket_client;

    char address_buffer[100];
    getnameinfo((struct sockaddr*)&client_address,
            client_len,
            address_buffer, sizeof(address_buffer), 0, 0,
            NI_NUMERICHOST);
    printf("New connection from %s\n", address_buffer);

    return true;
}

void Server::closeConnection()
{
    close(_listen);
}

Server::~Server(){}


