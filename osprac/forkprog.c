#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    pid_t pid1, pid2, pid3;
    pid1 = fork();
    if(pid1 == 0)
    {
        printf("Child process. PID = %d and parent pid = %d\n",getpid(),getppid());
        pid2 = fork();

        if(pid2 == 0)
        {
            printf("Grand Child 1. pid = %d and ppid = %d\n",getpid(), getppid());
            sleep(2);
            exit(0);
        }

        pid3 = fork();

        if(pid3 == 0)
        {
            printf("Grand Child 2. pid = %d and ppid = %d\n",getpid(), getppid());
            sleep(2);
            exit(0);
        }

        wait(NULL);
        wait(NULL);
        printf("Child 1 (PID = %d  and ppid = %d) finished waiting for grandchildren.\n", getpid(), getppid());
        exit(0);
    }

    wait(NULL);
    printf("Parent process (PID = %d) finished waiting for all children.\n", getpid());
}