#include "helperFunction.h"

HelperFunction::HelperFunction(/* args */)
{
}

HelperFunction::~HelperFunction()
{
}

void HelperFunction::parse_url(std::string url, std::string &hostname, std::string &port, std::string &path)
{
    std::string newUrl;
    std::cout << "URL : " << url << std::endl;

    ssize_t p = url.find("://");
    if(p > 0)
        newUrl.assign(url, p+3, url.size());
    else 
        newUrl = url;

    
    p = 0;
    p = newUrl.find("/");
    if(p > 0)
    {
        hostname.assign(newUrl, 0, p--);
        newUrl.assign(newUrl, p+2, newUrl.size());

        //Get path................
        p = newUrl.find("#");
        if(p)
            path.assign(newUrl, 0, p);
        else
            path = newUrl;
    }else
        hostname = newUrl;
    

    //Get hostname and port............
    ssize_t np = hostname.find(":");
    if(np > 0)
    {
        port.assign(hostname, np+1, hostname.size()+1);
        hostname.assign(hostname, 0, np);
    }
    else
        port = "80";


    std::cout << "Host name : " << hostname << std::endl;
    std::cout << "Port : " << port << std::endl;
    std::cout << "Path : " << path << std::endl;
    std::cout << std::endl;
}

