#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int Pid;
    int i;
    Pid = fork();
    if (Pid < 0)
    {
        printf("Child process creation failed. \n");
    }
    else if (Pid == 0)
    {
        /* Do parent operations. */
        for (i = 0; i < 49; i++)
        {
            printf("This is the parent operation! \n");
            sleep(1);
        }
    }
    else
    {
        /* Do child operations. */
        for (i = 0; i < 24; i++)
        {
            printf("This is the child operation! \n");
            sleep(2);
        }
    }
    return 0;
}
