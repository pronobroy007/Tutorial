#include <iostream>
#include "ModelA.h"
#include "ModelB.h"

int main()
{
    AirPlane *ma = new ModelA;    
    ma->fly();

    AirPlane *mb = new ModelB;    
    mb->fly();

    delete ma;
    delete mb;

	return 0;
}
