#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int pid;
    int bt;
    int at;
    int ct;
    int wt;
    int tat;
} *process;

void sort(process list, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - 1 - i; j++)
        {
            if(list[j].at > list[j + 1].at)
            {
                process temp = (process) malloc(sizeof(*list));
                *temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = *temp;
                free(temp);
            }
        }
    }
}

void fcfs(process list, int n)
{
    int time = 0;
    for(int i = 0; i < n; i++)
    {
        if(time < list[i].at)
            time = list[i].at;
        time += list[i].bt;
        list[i].ct = time;

        list[i].tat = list[i].ct - list[i].at;
        list[i].wt = list[i].tat - list[i].bt;
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
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);

    process list = (process) malloc(sizeof(*list) * n);

    int at, bt;
    for(int i = 0; i < n; i++)
    {
        printf("Enter the Arrival time and Burst time for process %d: ", i + 1);
        scanf("%d %d", &at, &bt);

        list[i].pid = i + 1;
        list[i].at = at;
        list[i].bt = bt;
        list[i].ct = 0;
        list[i].tat = 0;
        list[i].wt = 0;
}

    sort(list, n);
    fcfs(list, n);
    display(list, n);

    free(list);
    return 0;
}
