#include "client.h"

Client::Client()
{
    _ip = (char*)"127.0.0.1";
    _port = (char*)"5555";

    //_ip = "example.com";
    //_port = "80";

    bzero(&hints, sizeof(hints));

    sockOpt.push_back(SOCK_OPT("SO_BROADCAST", SOL_SOCKET, SO_BROADCAST));
    sockOpt.push_back(SOCK_OPT("SO_DEBUG", SOL_SOCKET, SO_DEBUG));
    sockOpt.push_back(SOCK_OPT("SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE));
    sockOpt.push_back(SOCK_OPT("SO_ERROR", SOL_SOCKET, SO_ERROR));
    sockOpt.push_back(SOCK_OPT("SO_KEEPALIVE",SOL_SOCKET, SO_KEEPALIVE));
    sockOpt.push_back(SOCK_OPT("SO_LINGER", SOL_SOCKET, SO_LINGER));
    sockOpt.push_back(SOCK_OPT("SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE));
    sockOpt.push_back(SOCK_OPT("SO_RCVBUF", SOL_SOCKET, SO_RCVBUF));
    sockOpt.push_back(SOCK_OPT("SO_SNDBUF", SOL_SOCKET, SO_SNDBUF));
    sockOpt.push_back(SOCK_OPT("SO_RCVLOWAT", SOL_SOCKET, SO_RCVLOWAT));
    sockOpt.push_back(SOCK_OPT("SO_SNDLOWAT", SOL_SOCKET, SO_SNDLOWAT));
    sockOpt.push_back(SOCK_OPT("SO_RCVTIMEO", SOL_SOCKET, SO_RCVTIMEO));
    sockOpt.push_back(SOCK_OPT("SO_SNDTIMEO", SOL_SOCKET, SO_SNDTIMEO));
    sockOpt.push_back(SOCK_OPT("SO_REUSEADDR",SOL_SOCKET, SO_REUSEADDR));
}

bool Client::init()
{
    //This is for Broke Pipe exception handler for sending to a client which is close.
	signal(SIGPIPE, SIG_IGN);    

    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(_ip, _port, &hints, &bind_addr);

	sock = socket(bind_addr->ai_family, bind_addr->ai_socktype, bind_addr->ai_protocol);
	if(sock < 0)
    {
		std::cout << "Error to open socket ..!" << std::endl;
        return false;
    }

    //socket option.
    for(int i = 0; i < sockOpt.size(); i++)
    {
        int optval;
        socklen_t optlen = sizeof(optval);

        getsockopt(sock, sockOpt[i].level, sockOpt[i].optName, (char*)&optval, &optlen);
        std::cout << "  "+ sockOpt[i].name +" value : " << optval << std::endl;
    }
    std::cout << std::endl;

    return true;
}

bool Client::connectServer()
{
    //Initilize server connection.
    if(!init())
        exit;

    //Connecting to server......
    if(connect(sock, bind_addr->ai_addr, bind_addr->ai_addrlen) != 0)
    {
        std::cout << "Error to connect server ..!" << std::endl;
        return false;
    }

    //socket option.
    for(int i = 0; i < sockOpt.size(); i++)
    {
        int optval;
        socklen_t optlen = sizeof(optval);

        getsockopt(sock, sockOpt[i].level, sockOpt[i].optName, (char*)&optval, &optlen);
        std::cout << "  "+ sockOpt[i].name +" value : " << optval << std::endl;
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
