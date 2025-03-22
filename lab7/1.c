#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork(); 

    if (pid1 == 0) {
        printf("Child 1, PID = %d, Parent PID = %d\n", getpid(), getppid());
        pid2 = fork(); 

        if (pid2 == 0) {
            printf("Child 3, PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            wait(NULL); 
        }
    } else { 
        pid2 = fork(); 

        if (pid2 == 0) {
            printf("Child 2, PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            wait(NULL); 
            wait(NULL); 
        }
    }
    return 0;
}


