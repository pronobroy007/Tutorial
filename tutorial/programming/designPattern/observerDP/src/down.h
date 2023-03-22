#ifndef _DOWN
#define _DOWN
#include "ijob.h"

class Down : public IJob
{
    public:
        std::string msg;

        Down();
            void execute(); 
        ~Down();
    
    private:
};


#endif
