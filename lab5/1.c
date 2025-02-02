// 1.FCFS algorithm implementation in C using structure / linked list
#include<stdio.h>
#include<stdlib.h>

struct node
{
    int pid;
    int arrival;
    int burst;
    int turnaround;
    int completion;
    int waiting;
    struct node* next;
};

void insertProcess(struct node** head, int pid, int arrival, int burst){
    struct node* newp = (struct node*) malloc(sizeof(struct node));
    newp->arrival = arrival;
    newp->pid = pid;
    newp->burst = burst;
    newp->completion = 0;
    newp->turnaround = 0;
    newp->waiting = 0;
    newp->next = NULL;

    if(*head == NULL || (*head)->arrival > arrival)
    {
        newp->next = *head;
        *head = newp;
        return;
    }

    struct node* temp = *head;
    while(temp->next != NULL && temp->next->arrival <= arrival)
        temp = temp->next;

    newp->next = temp->next;
    temp->next = newp;
}

void computeFCFS(struct node* head)
{
    int currenttime = 0;
    struct node* temp = head;

    while(temp != NULL)
    {
        if(currenttime < temp->arrival)
            currenttime = temp->arrival;

        temp->completion = currenttime + temp->burst;
        temp->turnaround = temp->completion - temp->arrival;
        temp->waiting = temp->turnaround - temp->burst;
        currenttime = temp->completion;

        temp = temp->next;
    }
}

void displayProcess(struct node* head)
{
    printf("\nFCFS Scheduling Results:\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    struct node* temp = head;
    while(temp != NULL) 
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", temp->pid, temp->arrival, temp->burst, temp->completion, temp->turnaround, temp->waiting);
        temp = temp->next;
    }
}

int main()
{
    struct node* head = NULL; 
    int n, pid, arrival, burst;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++)
    {
        printf("Enter Process ID, Arrival time and Burst time for process %d: ", i+1);
        scanf("%d %d %d", &pid, &arrival, &burst);
        insertProcess(&head, pid, arrival, burst);
    }

    computeFCFS(head);
    displayProcess(head);
    
    return 0;
}
