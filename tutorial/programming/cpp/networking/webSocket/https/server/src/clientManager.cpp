#include "clientManager.h"

ClientManager::ClientManager()
{ 
    bzero(response, BUFFER);
}

int ClientManager::get_client(fd_set &reads)
{
    for(int i = 0; i < _client_info_vec.size(); i++)
    {
        if(FD_ISSET(_client_info_vec[i].socket, &reads))
            return i;
    }
    return  -1;
}


bool ClientManager::drop_client(int index)
{
    _client_info_vec.erase(_client_info_vec.begin() + index);
    return false;
}


std::string ClientManager::get_client_address(int index)
{
    std::string ip;
    char buff[100];
    getnameinfo((struct sockaddr*)&_client_info_vec[index].client_addr,
            _client_info_vec[index].size,
            buff, sizeof(buff), 0, 0,
            NI_NUMERICHOST);
    ip = buff;
    return ip;
}


fd_set ClientManager::wait_on_client(int sock)
{
    fd_set master;
    FD_ZERO(&master);
    FD_SET(sock, &master);
    int max_sock = sock;

    for(int i = 0; i < _client_info_vec.size(); i++)
    {
        int s = _client_info_vec[i].socket;
        FD_SET(s, &master);
        if (s > max_sock)
            max_sock = s;
    }

    if (select(max_sock+1, &master, 0, 0, 0) < 0) {
        perror("select() failed");
        exit(1);
    }

    return master;
}



void ClientManager::server_response(int index, char* path)
{
    if(strcmp(path, "/") == 0)
        path = (char*)"/index.html";
    else if(strlen(path) > 100)
    {
        send400(index);
        return;
    }
    else if(strstr(path, ".."))
    {
        send404(index);
        return;
    }

    char full_path[128];
    sprintf(full_path, "public%s", path);

    //Open file to send response to server.
    std::ifstream input_file(full_path, std::ios::binary | std::ios::ate);
    if(!input_file.is_open())
    {
        send400(index);
        perror("Error to open file");
        return;
    }


    //Send response..
    std::string header;
    header = "HTTP/1.1 200 OK\r\n";
    header += "Connection: close\r\n";

    ssize_t cl = input_file.tellg();
    input_file.seekg(0, std::ios::beg);
    header += "Content-Length: " + std::to_string(cl) + "\r\n";

    std::string ct = get_content_type(full_path);
    header += "Content-Type: " + ct + "\r\n";
    header += "\r\n";
    send_all(_client_info_vec[index].ssl, (char*)header.c_str(), header.size());

    std::cout << "Response header : " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "Content-Length : " << cl << std::endl;
    std::cout << "Content-Type : " << ct << std::endl;
    std::cout << "Full path : " << full_path << std::endl;


   while(!input_file.eof())
   {
       input_file.read(response, BUFFER);
       //send file data ...........
       send_all(_client_info_vec[index].ssl, response, BUFFER);
   } 

   input_file.close();
   std::cout << "**********************************" << std::endl;
}

void ClientManager::send_all(SSL* ssl, char* msg, int len)
{
    while(len > 0)
    {
        int byte_send = SSL_write(ssl, msg, len);
        if(byte_send < 1)
            break;

        len -= byte_send;
    }
}


void ClientManager::send400(int index)
{
    const char *c400 = "HTTP/1.1 400 Bad Request\r\n"
        "Connection: close\r\n"
        "Content-Length: 11\r\n\r\nBad Request";
    send_all(_client_info_vec[index].ssl, (char*)c400, strlen(c400));
    drop_client(index);
}

void ClientManager::send404(int index)
{
    const char *c404 = "HTTP/1.1 404 Not Found\r\n"
        "Connection: close\r\n"
        "Content-Length: 9\r\n\r\nNot Found";
    send_all(_client_info_vec[index].ssl, (char*)c404, strlen(c404));
    drop_client(index);
}


void ClientManager::print()
{
    for (int i = 0; i < _client_info_vec.size(); i++)
        std::cout << _client_info_vec[i].socket << std::endl;
}

std::string ClientManager::get_content_type(const char* path) {
    std::string str;
    const char *last_dot = strrchr(path, '.');
    if (last_dot) {
        if (strcmp(last_dot, ".css") == 0)  str = "text/css";
        if (strcmp(last_dot, ".csv") == 0)  str = "text/csv";
        if (strcmp(last_dot, ".gif") == 0)  str = "image/gif";
        if (strcmp(last_dot, ".htm") == 0)  str = "text/html";
        if (strcmp(last_dot, ".html") == 0) str = "text/html";
        if (strcmp(last_dot, ".ico") == 0)  str = "image/x-icon";
        if (strcmp(last_dot, ".jpeg") == 0) str = "image/jpeg";
        if (strcmp(last_dot, ".jpg") == 0)  str = "image/jpeg";
        if (strcmp(last_dot, ".js") == 0)   str = "application/javascript";
        if (strcmp(last_dot, ".json") == 0) str = "application/json";
        if (strcmp(last_dot, ".png") == 0)  str = "image/png";
        if (strcmp(last_dot, ".pdf") == 0)  str = "application/pdf";
        if (strcmp(last_dot, ".svg") == 0)  str = "image/svg+xml";
        if (strcmp(last_dot, ".txt") == 0)  str = "text/plain";
        return str;
    }
    return "application/octet-stream";
}


ClientManager::~ClientManager()
{
}
