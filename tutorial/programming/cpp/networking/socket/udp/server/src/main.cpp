#include "../../lib/src/server.h"

void resp(Server &server);
int main(int argc, char const *argv[])
{
    Server server("5555");
    if(server.init())
    {
        while (true)
        {
            //........................................
            //Recv msg from server.
            char read[1024];
            struct sockaddr_storage client_addr;
            socklen_t len = sizeof(client_addr);
            int bytes_recv = recvfrom(server._listen, read, 1024, 0, (struct sockaddr *)&client_addr, &len);
            //Print Client Address.....................
            char address_buffer[100];
            getnameinfo((struct sockaddr *)&client_addr,
                        sizeof(client_addr),
                        address_buffer, sizeof(address_buffer), 0, 0,
                        NI_NUMERICHOST);
            printf("New connection from %s\n", address_buffer);
            //Print Message ...........................
            printf("%.*s\n", bytes_recv, read);

            //........................................
            //Send msg to server.
            char *hello = "Hello From Server";
            int bytes_send = sendto(server._listen, hello, strlen(hello), 0, (struct sockaddr *)&client_addr, len);
            std::cout << "Total Byte send : "<< bytes_send << std::endl;
            std::cout << std::endl;
        }

    }


    server.closeConnection();
    return 0;
}
