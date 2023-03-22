#include "../../lib/src/client.h"

int main()
{
    Client client;
    if(client.init())
    {
        //...............................................
        //Send Msg to server
        char* hello = "Hello From client";
        int bytes_send = sendto(client.sock, hello, strlen(hello), 0, client.bind_addr->ai_addr, client.bind_addr->ai_addrlen);
        std::cout << "Total send bytes : " << bytes_send << std::endl;

        //...............................................
        //Recv Msg from server
        char msg[1024];
        bzero(msg, 1024);
        socklen_t len;
        struct sockaddr_storage serv_addr;        
        recvfrom(client.sock, msg, 1024, 0, (struct sockaddr*)&serv_addr, &len);
        std::cout << msg << std::endl;
    }
    client.clientClose();
	return 0;
}
