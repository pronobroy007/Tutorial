#ifndef _IJOB
#define _IJOB
#include <iostream>

class IJob
{
    public:
        bool jobStatus;

        IJob() : jobStatus(false) {};
            virtual void execute() = 0; 
        virtual ~IJob(){};
    
};
#endif
