#include <stdio.h>

#define MAX_PROCESSES 100  

struct Process {
    int pid, at, bt, rt, wt, tat, ct;
};

void sortByArrivalTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void roundRobin(struct Process p[], int n, int timeQuantum) {
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    int queue[MAX_PROCESSES], front = 0, rear = 0; 
    int visited[MAX_PROCESSES] = {0}; 
    
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    queue[rear++] = 0; 
    visited[0] = 1;

    while (completed < n) {
        int index = queue[front++];  

        if (p[index].rt > 0) {
            int executeTime = (p[index].rt > timeQuantum) ? timeQuantum : p[index].rt;
            p[index].rt -= executeTime;
            time += executeTime;

            if (p[index].rt == 0) {
                completed++;
                p[index].ct = time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                total_wt += p[index].wt;
                total_tat += p[index].tat;
            }

            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].at <= time && p[i].rt > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            if (p[index].rt > 0) {
                queue[rear++] = index;  
            }
        }

        if (front == rear) { 
            for (int i = 0; i < n; i++) {
                if (p[i].rt > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, timeQuantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time of process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);
    
    roundRobin(p, n, timeQuantum);
    sortByArrivalTime(p,n);

    return 0;
}