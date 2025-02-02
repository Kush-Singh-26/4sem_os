#include <stdio.h>
#include <stdlib.h>

struct node {
    int pid;
    int arrival;
    int burst;
    int turnaround;
    int completion;
    int waiting;
    struct node* next;
};

void insertProcess(struct node** head, int pid, int arrival, int burst) {
    struct node* newp = (struct node*)malloc(sizeof(struct node));
    newp->arrival = arrival;
    newp->pid = pid;
    newp->burst = burst;
    newp->completion = 0;
    newp->turnaround = 0;
    newp->waiting = 0;
    newp->next = NULL;

    if (*head == NULL || (*head)->arrival > arrival) {
        newp->next = *head;
        *head = newp;
        return;
    }

    struct node* temp = *head;
    while (temp->next != NULL && temp->next->arrival <= arrival)
        temp = temp->next;

    newp->next = temp->next;
    temp->next = newp;
}

void computeSJF(struct node* head) {
    if (head == NULL) return;

    int current_time = 0;
    struct node* temp = NULL;
    struct node* completed = NULL;

    while (head != NULL) {
        struct node* shortest = NULL;
        struct node* prev = NULL;
        struct node* shortestPrev = NULL;

        temp = head;
        while (temp != NULL) {
            if (temp->arrival <= current_time) {
                if (shortest == NULL || temp->burst < shortest->burst) {
                    shortest = temp;
                    shortestPrev = prev;
                }
            }
            prev = temp;
            temp = temp->next;
        }

        if (shortest == NULL) {
            current_time++;
            continue;
        }

        if (shortestPrev == NULL) {
            head = shortest->next;
        } else {
            shortestPrev->next = shortest->next;
        }

        shortest->completion = current_time + shortest->burst;
        shortest->turnaround = shortest->completion - shortest->arrival;
        shortest->waiting = shortest->turnaround - shortest->burst;
        current_time = shortest->completion;

        shortest->next = completed;
        completed = shortest;
    }

    printf("\nSJF (Non-Preemptive) Scheduling Results:\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    while (completed != NULL) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               completed->pid, completed->arrival, completed->burst,
               completed->completion, completed->turnaround, completed->waiting);
        completed = completed->next;
    }
}

int main() {
    struct node* head = NULL;
    int n, pid, arrival, burst;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival time and Burst time for process %d: ", i + 1);
        scanf("%d %d %d", &pid, &arrival, &burst);
        insertProcess(&head, pid, arrival, burst);
    }

    computeSJF(head);
    return 0;
}