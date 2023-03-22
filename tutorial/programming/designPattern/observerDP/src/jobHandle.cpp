#include "jobHandle.h"

JobHandle::JobHandle() : RemmingJob(99999999), TotalThread(10) { }

void JobHandle::addJob(IJob *job)
{
    _jobs.push_back(job);
}

void JobHandle::clear()
{
    _jobs.clear();
    TotalThread = 10;
    RemmingJob = 99999999;
}

void JobHandle::removeJob(IJob *job)
{
    std::list<IJob*>::iterator it = _jobs.begin(); 
    while(it != _jobs.end())
    {
        if(*it == job)
            it = _jobs.erase(it);
        else
            it++;
    }
}


void JobHandle::complit()
{
    int index = 0;
    std::unique_ptr<std::thread[]> threads(new std::thread[TotalThread]);

    std::list<IJob*>::iterator it = _jobs.begin(); 
    for(;it != _jobs.end(); it++, index++)
    {
        //Wait until all thread finish jobs.
        if(index == TotalThread)
        {
            for(int i = 0; i < index; i++)
                threads[i].join();

            index = 0;
            sleep(2);
        }

        threads[index] = std::thread(&IJob::execute, std::ref(*it));
    }

    for(int i = 0; i < index; i++)
        threads[i].join();


    //Check if all job done successfully :
    //------------------------------------
        RemmingJob = _jobs.size();
        it = _jobs.begin(); 
        for(;it != _jobs.end(); it++)
            if((*it)->jobStatus == true)
                RemmingJob --;

        if(RemmingJob == 0)
            std::cout << "All jobs successfully Done @@@@@@@@@@@@@@@@ " << RemmingJob << std::endl;
}


JobHandle::~JobHandle() {}



