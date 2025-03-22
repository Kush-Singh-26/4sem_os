#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MSG_SIZE 100

void create_process_chain(int levels) {
    int fd[2];  
    char message[MSG_SIZE] = "Message from root";
    pipe(fd);  

    for (int i = 0; i < levels; i++) {
        pid_t pid = fork();

        if (pid == 0) { 
            close(fd[1]); 
            read(fd[0], message, MSG_SIZE - 1); 
            close(fd[0]);

            char new_message[MSG_SIZE];
            snprintf(new_message, MSG_SIZE, "%.50s -> Level %d", message, i+1);
            strcpy(message, new_message);

            pipe(fd); 
        } else { 
            close(fd[0]); 
            write(fd[1], message, strlen(message) + 1); 
            close(fd[1]);
            wait(NULL); 
            exit(0);
        }
    }

    printf("Final Message at last child: %s\n", message);
    exit(0);
}

int main() {
    int levels;
    printf("Enter number of levels: ");
    scanf("%d", &levels);
    create_process_chain(levels);
    return 0;
}
