#include "server.h"

int main()
{
	Server server((char*)"5555");
	if(server.init())
	{
		while (true)
		{
			fd_set reads;
			reads = server.wait_on_client(server._listen);	

			//For new connection.........
			if(FD_ISSET(server._listen, &reads))
				server.acceptClient();

			//For an existing connection..........
			//get_client() will check with FD_ISSET() and return which client is requesting.
			int index = server.get_client(reads);
			if (index >= 0) 
			{
				std::cout << "Get client : " << index << std::endl;
				char msg[4096];
				bzero(msg, 4096);
				server.recvRequest(index, msg, 4096);
				std::cout << "Request : " << std::endl;
				std::cout << "---------" << std::endl;
				std::cout << msg << std::endl;
				std::cout << "****************************************" << std::endl;
			}
			
		}//while
	}//IF 
	return 0;
}
