#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig)
{
    write(1, "\nI'm melting!! mmeeellttiiiingg.......\n", 39);
    _exit(0);
}
int main() 
{
    signal(SIGINT, sigint_handler);
    while(1)
    {
        printf("1.\n2,\n3.\n");
    }
    return 0;
}

