#include "client.h"
#include <string>

int main()
{
    std::string url = "https://www.youtube.com";
    url = "https://github.com/alireza-amirsamimi/xfce-panel-background-images/tree/master/images";
    //url = "127.0.0.1";
    Client client;
    if(client.connectServer(url, "443"))
	{
		client.send_req();
		client.recvResponse();
	}
    std::cout << std::endl;
    return 0;
}


