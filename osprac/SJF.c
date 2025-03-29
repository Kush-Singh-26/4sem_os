#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
} *process;


void sjf(process list, int n)
{
    int time = 0, completed = 0;
    int is_completed[n];
    for(int i =0 ;i<n;i++)
    {   
        is_completed[i] = 0;
    }

    while(completed != n)
    {
        int index = -1;
        int minbt = INT_MAX;

        for(int i = 0;i<n;i++)
        {
            if(list[i].at <= time && !is_completed[i])
            {
                if(list[i].bt < minbt)
                {
                    minbt = list[i].bt;
                    index = i;
                }

                else if(list[i].bt == minbt && list[i].at < list[index].at)
                    index = i;
            }
        }

        if(index == -1) // if no process has arrived then increment the time
            time++;
        
        else
        {
            time += list[index].bt;
            list[index].ct = time;
            list[index].tat = list[index].ct - list[index].at;
            list[index].wt = list[index].tat - list[index].bt;

            is_completed[index] = 1;
            completed++;
        }
    }
}

void display(process list, int n)
{
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", list[i].pid, list[i].at, list[i].bt, list[i].ct, list[i].tat, list[i].wt);
    }
}


int main()
{
    printf("Enter the number of processes : ");
    int n; scanf("%d",&n);
    process list = (process) malloc(sizeof(*list) * n);

    printf("Enter Arrival time and Burst time for each process.\n");

    for(int i =0;i<n;i++)
    {
        printf("Enter Arrival time and Burst time of process %d : ",i+1);
        scanf("%d%d",&list[i].at, &list[i].bt);
        list[i].pid = i;
        list[i].ct = 0;
        list[i].tat = 0;
        list[i].wt = 0;
    }

    sjf(list, n);
    display(list, n);

    free(list);
    return 0;
}