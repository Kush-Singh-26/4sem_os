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

void srtf(process list, int n)
{
	int time = 0, completed =0;
	int remaining_time[n];
	int iscompleted[n];
	for(int i =0;i<n;i++)
	{
		remaining_time[i] = list[i].bt;
	    iscompleted[i] = 0;
	}

	while(completed != n)
	{
		int index = -1;
		int minbt = INT_MAX;

		for(int i =0;i<n;i++)
		{
			if(list[i].at <= time && !iscompleted[i])
			{

				if(remaining_time[i] < minbt)
				{
					index = i;
					minbt = remaining_time[i];
				}
				else if(remaining_time[i] == minbt && list[i].at < list[index].at)
					index = i;
			}
		}

		if(index == -1)
			time++;

		else
		{
			remaining_time[index]--;
			time++;
			if(remaining_time[index] == 0)
			{
				list[index].ct = time;
				list[index].tat = list[index].ct - list[index].at;
				list[index].wt = list[index].tat - list[index].bt;

				iscompleted[index] = 1;
				completed++;
			}
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
    printf("Enter the Arrival and Burst Time for each process\n");
    
    for(int i =0 ;i<n;i++)
    {
	printf("Enter the arrival and burst time for process %d : ", i+1);
	scanf("%d%d", &list[i].at, &list[i].bt);
	list[i].pid = i+1;
	list[i].ct = 0;
	list[i].tat = 0;
	list[i].wt = 0;
    }

	srtf(list, n);
	display(list, n);
	free(list);
	return 0;
}
