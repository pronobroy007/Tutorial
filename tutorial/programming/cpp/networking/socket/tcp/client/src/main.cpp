#include "../../lib/src/client.h"

int main()
{
    Client client;
    if(client.connectServer())
    {
        while (true)
        {
            fd_set reads;
            FD_ZERO(&reads);
            //0 = Terminal input
            FD_SET(0, &reads);
            //This is incoming socket message.
            FD_SET(client.sock, &reads);

            if(select(client.sock+1, &reads, 0, 0, 0) < 0)
                perror("Faield select() function");

            //Now check for either read incoming message from socket or terminal input. 
            if(FD_ISSET(client.sock, &reads))
            {
                char msg[4096];
                int byte_read = recv(client.sock, msg, 4096, 0);
                if(byte_read < 1)break;

                printf("(%d bytes): %.*s", byte_read, byte_read, msg);
            }
            else
            {
                char msg[4096];
                if(!fgets(msg, 4069, stdin)) break; 
                client.send_all(client.sock, msg, strlen(msg));
            }
        }
    }
    
    client.clientClose();
	return 0;
}
