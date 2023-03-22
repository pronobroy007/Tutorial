#ifndef _MODELA
#define _MODELA
#include "AirPlane.h"

class ModelA : public AirPlane
{
    public:
        int hello;
        ModelA();
            void fly();
        ~ModelA();
    
    private:
};

#endif
