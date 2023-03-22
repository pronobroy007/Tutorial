#ifndef _JOBHANDLE
#define _JOBHANDLE
#include <thread>
#include <memory>
#include <unistd.h>
#include <list>
#include "ijob.h"

class JobHandle
{
    public:
        int RemmingJob;
        int TotalThread;

        JobHandle();
            void addJob(IJob *job);
            void removeJob(IJob *job);
            void clear();
            void complit();
        ~JobHandle();
    
    private:
        std::list<IJob*> _jobs;
};
#endif
