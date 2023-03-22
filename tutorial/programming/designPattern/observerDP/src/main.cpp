#include <iostream>
#include "down.h"
#include "jobHandle.h"

int main()
{
    JobHandle hand;

    Down d, e, f;
    d.msg = "hello";
    e.msg = "world";
    f.msg = "how are you";

    hand.addJob(&d);
    hand.addJob(&e);
    hand.addJob(&f);

    hand.complit();
	return 0;
}
