#include "client.h"

Client::Client()
{
    _ip = "127.0.0.1";
    _port = "5555";
    bzero(&hints, sizeof(hints));
}

bool Client::init()
{
    //This is for Broke Pipe exception handler for sending to a client which is close.
	signal(SIGPIPE, SIG_IGN);    

    hints.ai_socktype = SOCK_DGRAM;
    getaddrinfo(_ip, _port, &hints, &bind_addr);

	sock = socket(bind_addr->ai_family, bind_addr->ai_socktype, bind_addr->ai_protocol);
	if(sock < 0)
    {
		std::cout << "Error to open socket ..!" << std::endl;
        return false;
    }

    return true;
}

void Client::clientClose()
{
    close(sock);
}

Client::~Client()
{
    if(sock)
        close(sock);
}
