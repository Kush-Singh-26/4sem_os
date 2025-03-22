#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MSG_SIZE 200  

void create_ring(int n, int direction) {
    int pipes[n][2];  
    char message[MSG_SIZE] = "Initial message";

    for (int i = 0; i < n; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe creation failed");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0) {  
            int prev = (direction == 1) ? (i - 1 + n) % n : (i + 1) % n;  
            int next = (direction == 1) ? (i + 1) % n : (i - 1 + n) % n;  

            close(pipes[i][1]);  
            ssize_t bytesRead = read(pipes[i][0], message, MSG_SIZE - 1);
            close(pipes[i][0]);  

            if (bytesRead > 0) {
                message[bytesRead] = '\0';  
            } else {
                strncpy(message, "Error: No message received", MSG_SIZE - 1);
                message[MSG_SIZE - 1] = '\0';
            }

            char new_message[MSG_SIZE];
            snprintf(new_message, MSG_SIZE, "%.150s -> P%d", message, i);
            strncpy(message, new_message, MSG_SIZE - 1);
            message[MSG_SIZE - 1] = '\0';  

            close(pipes[next][0]);  
            write(pipes[next][1], message, strlen(message) + 1);
            close(pipes[next][1]);  

            exit(0);  
        }
    }

    close(pipes[0][0]);  
    write(pipes[0][1], message, strlen(message) + 1);
    close(pipes[0][1]);  

    int last = (direction == 1) ? (n - 1) : 0;  
    close(pipes[last][1]);  
    read(pipes[last][0], message, MSG_SIZE - 1);
    close(pipes[last][0]);  

    printf("Final message received by parent: %s\n", message);

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Ring message passing completed in %s direction.\n", direction == 1 ? "Clockwise" : "Anti-clockwise");
}

int main() {
    int n, direction;
    
    printf("Enter number of processes in the ring: ");
    if (scanf("%d", &n) != 1 || n < 2) {
        printf("Ring topology requires at least 2 processes!\n");
        return 1;
    }

    printf("Enter direction (1 for Clockwise, 2 for Anti-clockwise): ");
    if (scanf("%d", &direction) != 1 || (direction != 1 && direction != 2)) {
        printf("Invalid direction! Enter 1 or 2.\n");
        return 1;
    }

    create_ring(n, direction);
    return 0;
}