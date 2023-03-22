#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    char ch[20];

    strcpy(ch, argv[1]);
    printf("%s", ch);
    return 0;
}