#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int i;

    for (i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            printf("Child %d, PID = %d, Parent PID = %d\n", i+1, getpid(), getppid());
            sleep(2); 
            exit(0);
        }
    }

    for (i = 0; i < 3; i++) {
        wait(NULL); 
    }

    printf("Parent process (PID = %d) finished waiting for all children.\n", getpid());
    return 0;
}
