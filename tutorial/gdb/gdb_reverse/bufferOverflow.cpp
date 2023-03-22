#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void initialize(int *array, int size) {
	//here array = values[10]
	//if we see stack address of &p = 0x7fffffffe058 and starting address &values[0] = 0x7fffffffe030
	//and 0x7fffffffe058 - 0x7fffffffe030 = 40. 40 mean (10 * int) byte which is array size.
	//but this loop will go 0-10 total 11 which mean array[10]=*p in stack

	//This is buffer overflow. we are writing someone else value.
    for (int i = 0; i <= size; ++i)
        array[i] = 0;
}

int main(void) {
	//In address of p we have heap memory location. but p have an address on stack.
	//stack address p = 0x55555556ae70
    int *p = new int;

	//values[0] = 0x7fffffffe030
	//values[9] = 0x7fffffffe054
    int values[10];

    *p = 37;
    initialize(values, 10);
    printf("*p = %d\n", *p);
	delete p;
    return 0;
}
