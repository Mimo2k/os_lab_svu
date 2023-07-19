#include <stdio.h>

#define MAX_PROCESS 10

void calculateCompletionTime(int burstTimes[], int completionTimes[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        currentTime += burstTimes[i];
        completionTimes[i] = currentTime;
    }
}

void calculateTurnaroundTime(int arrivalTimes[], int completionTimes[], int turnaroundTimes[], int n) {
    for (int i = 0; i < n; i++) {
        turnaroundTimes[i] = completionTimes[i] - arrivalTimes[i];
    }
}

void calculateWaitingTime(int burstTimes[], int turnaroundTimes[], int waitingTimes[], int n) {
    for (int i = 0; i < n; i++) {
        waitingTimes[i] = turnaroundTimes[i] - burstTimes[i];
    }
}

void calculateAverageTimes(int turnaroundTimes[], int waitingTimes[], int n, float *avgWaitingTime, float *avgTurnaroundTime, float *avgCompletionTime) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalCompletionTime = 0;
    
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
        totalCompletionTime += turnaroundTimes[i] + waitingTimes[i];
    }
    
    *avgWaitingTime = (float) totalWaitingTime / n;
    *avgTurnaroundTime = (float) totalTurnaroundTime / n;
    *avgCompletionTime = (float) totalCompletionTime / n;
}

void displayGanttChart(int processIDs[], int n, int completionTimes[]) {
    printf("Gantt Chart:\n");
    printf("-----------\n");
    
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processIDs[i]);
    }
    
    printf("|\n");
    printf("-----------\n");
    printf("0 ");
    
    for (int i = 0; i < n; i++) {
        printf("  %d ", completionTimes[i]);
    }
    
    printf("\n\n");
}

void displayResults(int processIDs[], int arrivalTimes[], int burstTimes[], int completionTimes[], int turnaroundTimes[], int waitingTimes[], int n, float avgWaitingTime, float avgTurnaroundTime, float avgCompletionTime) {
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processIDs[i], arrivalTimes[i], burstTimes[i],
               completionTimes[i], turnaroundTimes[i], waitingTimes[i]);
    }
    
    printf("Average waiting time: %.2f\n", avgWaitingTime);
    printf("Average turnaround time: %.2f\n", avgTurnaroundTime);
    printf("Average completion time: %.2f\n", avgCompletionTime);
}

int main() {
    int n;
    int processIDs[MAX_PROCESS];
    int arrivalTimes[MAX_PROCESS];
    int burstTimes[MAX_PROCESS];
    int completionTimes[MAX_PROCESS];
    int turnaroundTimes[MAX_PROCESS];
    int waitingTimes[MAX_PROCESS];
    float avgWaitingTime, avgTurnaroundTime, avgCompletionTime;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter the arrival time and burst time for each process:\n");
    
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        
        printf("Process ID: ");
        scanf("%d", &processIDs[i]);
        
        printf("Arrival time: ");
        scanf("%d", &arrivalTimes[i]);
        
        printf("Burst time: ");
        scanf("%d", &burstTimes[i]);
        
        printf("\n");
    }
    
    calculateCompletionTime(burstTimes, completionTimes, n);
    calculateTurnaroundTime(arrivalTimes, completionTimes, turnaroundTimes, n);
    calculateWaitingTime(burstTimes, turnaroundTimes, waitingTimes, n);
    calculateAverageTimes(turnaroundTimes, waitingTimes, n, &avgWaitingTime, &avgTurnaroundTime, &avgCompletionTime);
    
    displayGanttChart(processIDs, n, completionTimes);
    displayResults(processIDs, arrivalTimes, burstTimes, completionTimes, turnaroundTimes, waitingTimes, n, avgWaitingTime, avgTurnaroundTime, avgCompletionTime);
    
    return 0;
}
