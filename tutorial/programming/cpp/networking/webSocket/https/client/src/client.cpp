#include "client.h"

Client::Client()
{
    //Initialize the OpenSSL library. 
    SSL_library_init();
    //To causes OpenSSL to load all available algorithms. Alternately, 
    //you could load only the algorithms you know are needed. For our 
    //purposes, it is easy to load them all. 
    OpenSSL_add_all_algorithms();
    //causes OpenSSL to load error messages when something goes wrong
    SSL_load_error_strings();
    

    bzero(&hints, sizeof(hints));
}

bool Client::connectServer(std::string url, std::string port)
{
    parse_url(url, _hostname, _port, _path);
    _port = port;
    _ip = _hostname;

    //This is for Broke Pipe exception handler for sending to a client which is close.
	signal(SIGPIPE, SIG_IGN);    


    //Creat TCP Connectin normally.
    std::cout << "IP and PORT : " << _ip << " " << _port << std::endl;
    hints.ai_socktype = SOCK_STREAM;
    if(getaddrinfo(_ip.c_str(), _port.c_str(), &hints, &bind_addr))
    {
        perror("Faield to getaddrinfo()");
        return false;
    }

	sock = socket(bind_addr->ai_family, bind_addr->ai_socktype, bind_addr->ai_protocol);
	if(sock < 0)
    {
		std::cout << "Error to open socket ..!" << std::endl;
        return false;
    }

    //Connecting to server......
    if(connect(sock, bind_addr->ai_addr, bind_addr->ai_addrlen) != 0)
    {
        perror("Error to connect server ..!");
        return false;
    }
    freeaddrinfo(bind_addr); 

    /*
    * Make TLS cnnection :
	* ####################
    *
    * You can think of this object as a sort of factory for SSL/TLS connections. 
    * It holds the initial settings that you want to use for your connections. 
    * Most programs only need to create one SSL_CTX object, 
	* and they can reuse it for all their connections.
    * 
    * We use TLS_client_method(), which indicates that we want general-purpose, 
    * version-flexible TLS methods available. Our client automatically negotiates 
    * the best mutually supported algorithm with the server upon connecting.
    */
    _ctx = SSL_CTX_new(TLS_client_method());
    if(!_ctx)
    {
        perror("Faiels SSL_CTX_new()");
        return false;
    }

	/*
    * SSL_new() is used to create an SSL object. This object is used 
    * to track the new SSL/TLS connection.
    */
    _ssl = SSL_new(_ctx);
    if(!_ssl)
    {
        std::cout << "SSL_new() faield" << std::endl;
        return false;
    }

    /* 
    * We then use SSL_set_tlsext_host_name() to set the domain for the 
    * server we are trying to connect to. This allows OpenSSL to use SNI. 
    * This call is optional, but without it, the server does not know which 
    * certificate to send in the case that it hosts more than one site.
    */
    if (!SSL_set_tlsext_host_name(_ssl, _ip.c_str())) 
    {
        std::cout << "SSL_set_tlsext_host_name() failed." << std::endl;
        return false;
    }

    /*
    * Finally, we call SSL_set_fd() and SSL_connect() to initiate 
    * the new TLS/SSL connection on our existing TCP socket.
    */
    SSL_set_fd(_ssl, sock);
    if ( SSL_connect(_ssl) == -1) {
        perror("SSL_connect() failed.");
        return false;
    }

    printf ("SSL/TLS using %s\n", SSL_get_cipher(_ssl));
    std::cout << "Connected" << std::endl;

    /*
    * Certificate :
    *############### 
    * 
    * Once the TLS connection is established, we can use the SSL_get_peer_certificate() 
    * function to get the server's certificate. 
    * It's also easy to print the certificate subject and issuer, 
    */
    X509 *cert = SSL_get_peer_certificate(_ssl);
    if(!cert)
        perror("SSL_get_peer_certificate() failed");

    char *tmp;
    if (tmp = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0)) {
        printf("\nsubject: %s\n", tmp);
        OPENSSL_free(tmp);
    }

    if (tmp = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0)) {
        printf("issuer: %s\n", tmp);
        OPENSSL_free(tmp);
    }

    /*
    * In order for OpenSSL to successfully verify the certificate, 
    * we must tell it which certificate authorities we trust. 
    * This can be done by using the SSL_CTX_load_verify_locations() function.
    * It must be passed the filename that stores all of the trusted root certificates.
    if (!SSL_CTX_load_verify_locations(_ctx, "trusted.pem", 0)) {
        fprintf(stderr, "SSL_CTX_load_verify_locations() failed.\n");
        ERR_print_errors_fp(stderr);
        return 1;
    }
    */
    
    /*
    * OpenSSL automatically verifies the certificate during 
    * the TLS/SSL handshake. You can get the verification 
    * results using the SSL_get_verify_result() function
    * Function returns X509_V_OK, then the certificate chain was verified by OpenSSL 
    */
    long vp = SSL_get_verify_result(_ssl);
    if (vp == X509_V_OK) {
        printf("Certificates verified successfully.\n");
    } else {
        printf("Could not verify certificates: %ld\n", vp);
    }

    X509_free(cert);
    std::cout << std::endl;

    return true;
}




/******************************************
*   Send and Recv functin..
*******************************************/
void Client::send_req()
{    
    std::string sBuff;
    sBuff = "GET /" + _path + " HTTP/1.1\r\n";
    sBuff += "Host: " + _hostname + ":" + _port + "\r\n";//":" + path + "\r\n";
    sBuff += "Connection: close\r\n";
    //Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0
    sBuff += "User-Agent: honpwc https_get 1.0\r\n";
    sBuff += "\r\n";
    char buff[sBuff.size() + 1];
    sBuff.copy(buff, sBuff.size());
    std::cout << "Rsquest : " << buff << std::endl;

    std::cout << SSL_write(_ssl, buff, strlen(buff)) << std::endl;;
}


bool Client::recvResponse() 
{
    char *body = 0;
    std::ofstream out;
    out.open(_hostname + ".html");
    if(!out.is_open())
        perror("Faield to open file");

    int p = 0;
    while (true)
    {
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(sock, &reads);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 200;

        if (select(sock+1, &reads, 0, 0, &timeout) < 0) {
            perror("select() failed. (%d)\n");
            return 1;
        }

        if(FD_ISSET(sock, &reads))
        {
            char msg[4096];
            int len = 4096;

            int byte_recv = SSL_read(_ssl, msg, len);
            if(byte_recv < 1)
                break;

            if(!body && (body = strstr(msg, "\r\n\r\n")))
                out.write(body + 4, strlen(body));
            else
                out.write(msg, byte_recv);

            p += byte_recv;
			std::cout << body << std::endl;
        }
    } 
    std::cout << "File Received !" << std::endl;
    return true;
}
//##########################################################
    



void Client::clientClose()
{
    SSL_shutdown(_ssl);
    SSL_free(_ssl);
    close(sock);
    SSL_CTX_free(_ctx);
}

Client::~Client()
{
    if(sock)
    {
        SSL_shutdown(_ssl);
        SSL_free(_ssl);
        close(sock);
        SSL_CTX_free(_ctx);
        std::cout << "Clear Everything ... ..." << std::endl;
    }
}
