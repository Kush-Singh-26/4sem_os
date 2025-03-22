#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid;
    int arrival;
    int burst;
    int turnaroundtime;
    int completion;
    int waiting;
    int remaining;
    struct process* next;
} *head = NULL;

void insert_process(int pid, int at, int bt)
{
    struct process* new_proc = (struct process*) malloc(sizeof(struct process));
    new_proc->arrival = at;
    new_proc->burst = bt;
    new_proc->pid = pid;
    new_proc->completion = 0;
    new_proc->remaining = bt;
    new_proc->next = NULL;
    new_proc->waiting = 0;
    new_proc->turnaroundtime = 0;

    if(head == NULL)
    {
        head = new_proc;
    }
    else
    {
        struct process* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_proc;
    }
}

struct process* find_shortest_time(int current_time)
{
    struct process *shortest = NULL, *temp = head;
    while(temp != NULL)
    {
        if(temp->arrival <= current_time && temp->remaining >0)
        {
            if(shortest == NULL || temp->remaining < shortest->remaining)
            {
                shortest = temp;
            }
        }
        temp = temp->next;
    }
    return shortest;
}

void execute_sjf()
{
    int time = 0, completed = 0, total_process = 0;
    struct process* temp = head;

    while(temp != NULL)
    {
        total_process++;
        temp = temp->next;
    }

    while(completed < total_process)
    {
        struct process* shortest = find_shortest_time(time);
        if(shortest == NULL)
        {
            time++;
            continue;
        }

        shortest->remaining--;
        time++;

        if(shortest->remaining == 0)
        {
            shortest->completion = time;
            shortest->turnaroundtime = shortest->completion - shortest->arrival;
            shortest->waiting = shortest->turnaroundtime - shortest->burst;
            completed++;
        }
    }
}

void display_results() {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    struct process *temp = head;
    while (temp) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", temp->pid, temp->arrival, temp->burst, 
               temp->completion, temp->turnaroundtime, temp->waiting);
        temp = temp->next;
    }
}

int main() {
    int n, at, bt;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &at, &bt);
        insert_process(i + 1, at, bt);
    }

    execute_sjf();
    display_results();
    return 0;
}