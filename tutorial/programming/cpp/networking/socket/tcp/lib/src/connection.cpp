#include "connection.h"

Connection::Connection()
{
}

bool Connection::send_all(int sock, char *msg, int len)
{
    int ptr = 0;
    while (len > 0)
    {
        int size = write(sock, msg, len);
        if (size <= 0)
            return false;

        len -= size;
        ptr += size;
    }
    //std::cout << "Total Send : " << ptr << std::endl;
    usleep(10);
    return true;
}


bool Connection::recv_all(int sock, char *msg, int len)
{
    char *ptr = (char*)msg;
    while (len > 0)
    {
        int byte_recv = recv(sock, ptr, len, 0);
        if(byte_recv <= 0)
            return false;

        ptr += byte_recv;
        len -= byte_recv;
    }
    //std::cout << "Total Recv : " << len << std::endl;
    return true;
}

Connection::~Connection()
{
}
