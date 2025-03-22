#include <stdio.h>

struct Process {
    int id;        
    int at;        
    int bt;        
    int rt;        
    int wt;        
    int tat;       
    int ct;        
};

void roundRobin(struct Process p[], int n, int timeQuantum) {
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                int executeTime = (p[i].rt > timeQuantum) ? timeQuantum : p[i].rt;
                p[i].rt -= executeTime;
                time += executeTime;
                
                if (p[i].rt == 0) {
                    completed++;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    total_wt += p[i].wt;
                    total_tat += p[i].tat;
                }
            }
        }
        
        if (completed == 0) {
            time++;
        }
    }
    
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, timeQuantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    while(getchar() != '\n'); 
    
    struct Process p[n];
    
    
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time of process %d: ", p[i].id);
        while (scanf("%d %d", &p[i].at, &p[i].bt) != 2) {
            printf("Invalid input. Please enter two numbers: ");
            while(getchar() != '\n'); 
        }
        p[i].rt = p[i].bt;
        while(getchar() != '\n'); 
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);
    
    roundRobin(p, n, timeQuantum);
    return 0;
}