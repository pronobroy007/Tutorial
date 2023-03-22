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
    _port = port;
    _ip = url;

    //This is for Broke Pipe exception handler for sending to a client which is close.
	signal(SIGPIPE, SIG_IGN);    


    //Creat TCP Connectin normally.
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
    
    
   
    std::cout << "Connected" << std::endl;
    return true;
}

bool Client::procMsg(std::string msg, char* recvBuffer, int expecting)
{
    if(sendRequest(msg.c_str(), msg.size()))
        return recvResponse(recvBuffer, expecting);

    return false;
}




bool Client::sendRequest(const char* msg, int len)
{
    std::cout << "C : " << msg;
    //int byte_send = send(sock, msg, len, 0);
    int byte_send = SSL_write(_ssl, msg, len);
    if(byte_send < 1)
    {
        perror("Faield to send()");
        return false;
    }
    return true;
}

bool Client::recvResponse(char* msg, int expecting)
{
    std::cout << "S : ";
    int r = 0; 
    char* p = (char*)msg;
    bzero(msg, BUFFERSIZE);

    //int byte_recv = recv(sock, p + r, BUFFERSIZE - r, 0);
    int byte_recv = SSL_read(_ssl, p + r, BUFFERSIZE - r);
    if(byte_recv < 1)
    {
        perror("Connection drop");
        exit(1);
    }

    r += byte_recv;
    std::cout << msg << std::endl;

    if(parse_response(msg) != expecting)
        return false;

    return true;    
}

int Client::parse_response(char* msg)
{
    char* p = msg;
    if(!p[0] || !p[1] || !p[2]) return 0;

    if(isdigit(p[0]) && isdigit(p[1]) && isdigit(p[2]))
        return atoi(p);

    return 0;
}
    
void Client::clientClose()
{
    close(sock);
}

Client::~Client()
{
    if(sock)
        close(sock);
}
 
