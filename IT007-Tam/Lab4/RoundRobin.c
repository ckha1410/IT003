#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SORT_BY_ARRIVAL 0
#define SORT_BY_PID 1
#define SORT_BY_BURST 2
#define SORT_BY_START 3

typedef struct {
    int iPID;
    int iArrival, iBurst;
    int iStart, iFinish, iWaiting, iResponse, iTaT, iRemaining;
} PCB;

void inputProcess(int n, PCB P[]) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        P[i].iPID = i + 1;
        P[i].iArrival = rand() % 19 + 1;
        P[i].iBurst = rand() % 7 + 5;
        P[i].iRemaining = P[i].iBurst; P[i].iStart = 0;
        printf("Process ID: %d, Arrival Time: %d, Burst Time: %d\n", P[i].iPID, P[i].iArrival, P[i].iBurst);
    }
}

void printProcess(int n, PCB P[]) {
    printf("PID\tArrival\tBurst\tStart\tFinish\tWaiting\tTaT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].iPID, P[i].iArrival, P[i].iBurst, P[i].iStart, P[i].iFinish,
               P[i].iWaiting, P[i].iTaT);
    }
}

void exportGanttChart(int n, PCB P[]) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| %d - %d | P%d ", P[i].iStart, P[i].iFinish, P[i].iPID);
    }
    printf("|\n");
}

void pushProcess(int *n, PCB P[], PCB Q) {
    P[*n] = Q;
    (*n)++;
}

void removeProcess(int *n, int index, PCB P[]) {
    for (int i = index; i < *n - 1; i++) {
        P[i] = P[i + 1];
    }
    (*n)--;
}

int swapProcess(PCB *P, PCB *Q) {
    PCB temp = *P;
    *P = *Q;
    *Q = temp;
    return 1;
}

int partition(PCB P[], int low, int high, int iCriteria) {
    PCB pivot = P[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        int condition = 0;
        if (iCriteria == SORT_BY_ARRIVAL) {
            condition = (P[j].iArrival < pivot.iArrival);
        } else if (iCriteria == SORT_BY_PID) {
            condition = (P[j].iPID < pivot.iPID);
        } else if (iCriteria == SORT_BY_BURST) {
            condition = (P[j].iBurst < pivot.iBurst);
        } else if (iCriteria == SORT_BY_START) {
            condition = (P[j].iStart < pivot.iStart);
        }
        if (condition) {
            i++;
            swapProcess(&P[i], &P[j]);
        }
    }
    swapProcess(&P[i + 1], &P[high]);
    return i + 1;
}

void quickSort(PCB P[], int low, int high, int iCriteria) {
    if (low < high) {
        int pi = partition(P, low, high, iCriteria);
        quickSort(P, low, pi - 1, iCriteria);
        quickSort(P, pi + 1, high, iCriteria);
    }
}

void calculateAWT(int n, PCB P[]) {
    int totalWaiting = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += P[i].iWaiting;
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaiting / n);
}

void calculateATaT(int n, PCB P[]) {
    int totalTaT = 0;
    for (int i = 0; i < n; i++) {
        totalTaT += P[i].iTaT;
    }
    printf("Average Turnaround Time: %.2f\n", (float)totalTaT / n);
}

int is_null(int n, PCB P[]) {
    for (int i = 0; i < n; i++)
        if (P[i].iPID != 0) return 1;
    return 0;
}

int main() {
    PCB Input[10];
    PCB ReadyQueue[10];
    PCB TerminatedArray[10];
    int iNumberOfProcess, currentTime = 0, q;
    printf("Please input number of Process: ");
    scanf("%d", &iNumberOfProcess);
    printf("Please input time quantum: ");
    scanf("%d", &q);
    int iRemain = iNumberOfProcess, iReady = 0, iTerminated = 0;
    inputProcess(iNumberOfProcess, Input);

    quickSort(Input, 0, iNumberOfProcess - 1, SORT_BY_ARRIVAL);
    pushProcess(&iReady, ReadyQueue, Input[0]);
    removeProcess(&iRemain, 0, Input);
    ReadyQueue[0].iStart = ReadyQueue[0].iArrival;

    currentTime = ReadyQueue[0].iArrival;
    if (ReadyQueue[0].iRemaining <= q)
        ReadyQueue[0].iFinish = ReadyQueue[0].iRemaining + ReadyQueue[0].iArrival;
    else ReadyQueue[0].iFinish = ReadyQueue[0].iArrival + q;

    printf("\n===== Round Robin Scheduling =====\n");
    while (iTerminated < iNumberOfProcess) {
        if (ReadyQueue[0].iRemaining <= q)
                ReadyQueue[0].iFinish = currentTime + ReadyQueue[0].iRemaining;
        else ReadyQueue[0].iFinish = currentTime + q;
        while (iRemain > 0) {
            if (Input[0].iArrival <= ReadyQueue[0].iFinish) {
                pushProcess(&iReady, ReadyQueue, Input[0]);
                removeProcess(&iRemain, 0, Input);
                continue;
            }
            else if (is_null(iReady, ReadyQueue) == 0) {
                pushProcess(&iReady, ReadyQueue, Input[0]);
                removeProcess(&iRemain, 0, Input);
                ReadyQueue[0].iStart = ReadyQueue[0].iArrival;
                ReadyQueue[0].iFinish = ReadyQueue[0].iStart + ReadyQueue[0].iBurst;
                currentTime = ReadyQueue[0].iArrival;
                continue;
            } else break;
        }

        if (iReady > 0) {
            if (ReadyQueue[0].iRemaining <= q) {
                if (ReadyQueue[0].iStart == 0)
                    ReadyQueue[0].iStart = currentTime;
            printf("| %d - %d | P%d ", currentTime, currentTime + ReadyQueue[0].iRemaining,
                                        ReadyQueue[0].iPID);
            currentTime += ReadyQueue[0].iRemaining;
            ReadyQueue[0].iRemaining = 0;
            ReadyQueue[0].iFinish = currentTime;
            ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;
            ReadyQueue[0].iWaiting = ReadyQueue[0].iTaT - ReadyQueue[0].iBurst;
            pushProcess(&iTerminated, TerminatedArray, ReadyQueue[0]);
            removeProcess(&iReady, 0, ReadyQueue);
            } else {
                if (ReadyQueue[0].iStart == 0)
                    ReadyQueue[0].iStart = currentTime;
                printf("| %d - %d | P%d ", currentTime, currentTime + q, ReadyQueue[0].iPID);
                currentTime += q;
                ReadyQueue[0].iRemaining -= q;
                pushProcess(&iReady, ReadyQueue, ReadyQueue[0]);
                removeProcess(&iReady, 0, ReadyQueue);
            }
        }
    }

    printf("\n");
    quickSort(TerminatedArray, 0, iTerminated - 1, SORT_BY_PID);
    printProcess(iTerminated, TerminatedArray);
    calculateAWT(iTerminated, TerminatedArray);
    calculateATaT(iTerminated, TerminatedArray);

    return 0;
}
