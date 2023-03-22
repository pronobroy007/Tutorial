#include "../../lib/src/server.h"

void resp(Server &server);
int main(int argc, char const *argv[]) 
{
	Server server((char*)"5555");
	server.init();
    while(true)
    {
        fd_set reads;
        reads = server.master;
        if(select(server.max_sock+1, &reads, 0, 0, 0) < 0)
		{
			perror("Faield select()");
			break;
		}
        for(int i = 0; i <= server.max_sock; i++)
        {
            if(FD_ISSET(i, &reads))
            {
                //................................................
                //This is for request from new client.
                if (i == server._listen) 
					server.acceptClient();
                //................................................
                //This is for an established client request.
                else
                {
                    char msg[1024];
                    int bytes_received = recv(i, msg, 1024, 0);
                    if (bytes_received < 1) 
                    {
                        FD_CLR(i, &server.master);
                        close(i);
                        std::cout << "Client Lost............." << std::endl;
                        continue;
                    }
                    std::cout << "RECV : " << msg << std::endl; 

                    for (int j = 0; j < bytes_received; ++j)
                        msg[j] = toupper(msg[j]);

                    server.send_all(i, msg, bytes_received);
                }
            }//FD_ISSET
        }//Foor loop
    }//While loop

	server.closeConnection();
	return 0;
}
