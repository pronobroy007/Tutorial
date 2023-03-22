#ifndef CLIENT
#define CLIENT

#include "connection.h"

class Client : public Connection
{
    public:
        int sock;

        Client();
            bool connectServer();
            void clientClose();
        ~Client();

    private:
        //Function ...............
        bool init();
        std::vector<SOCK_OPT> sockOpt;
};


#endif