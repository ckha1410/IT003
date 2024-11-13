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
    int iStart, iFinish, iWaiting, iResponse, iTaT;
} PCB;

void inputProcess(int n, PCB P[]) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        P[i].iPID = i + 1;
        P[i].iArrival = rand() % 19;
        P[i].iBurst = rand() % 7 + 5;
        P[i].iStart = P[i].iFinish = P[i].iWaiting = P[i].iResponse = P[i].iTaT = 0;
        printf("Process ID: %d, Arrival Time: %d, Burst Time: %d\n",
                P[i].iPID, P[i].iArrival, P[i].iBurst);
    }
}

void printProcess(int n, PCB P[]) {
    printf("PID\tArrival\tBurst\tStart\tFinish\tWaiting\tResponse\tTaT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n", P[i].iPID, P[i].iArrival, P[i].iBurst,
                        P[i].iStart, P[i].iFinish, P[i].iWaiting, P[i].iResponse, P[i].iTaT);
    }
}

void exportGanttChart (int n, PCB P[]) {
    printf("Gantt Chart:\n");
    printf("| 0 - %d | P%d ", P[0].iFinish, P[0].iPID);
    // Print process IDs
    for (int i = 1; i < n; i++) {
        printf("| %d - %d | P%d ", P[i-1].iFinish, P[i].iFinish, P[i].iPID);
    }
    printf("|\n ");
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

int main() {
    PCB Input[10];
    PCB ReadyQueue[50];
    PCB TerminatedArray[10];
    int iNumberOfProcess;
    PCB Gantt[50];
    int burstmap[50];
    int startmap[50];
    for (int i = 0; i < 50; i++) {
        startmap[i] = -1;
    }

    printf("Please input number of Process: ");
    scanf("%d", &iNumberOfProcess);
    int iRemain = iNumberOfProcess, iReady = 0, iTerminated = 0, iGantt = 0;
    inputProcess(iNumberOfProcess, Input);

    for (int i = 0; i < iNumberOfProcess; i++)
        burstmap[Input[i].iPID]  = Input[i].iBurst;

    quickSort(Input, 0, iNumberOfProcess - 1, SORT_BY_ARRIVAL);
    pushProcess(&iReady, ReadyQueue, Input[0]);
    removeProcess(&iRemain, 0, Input);
    ReadyQueue[0].iStart = ReadyQueue[0].iArrival;
    ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
    ReadyQueue[0].iFinish = ReadyQueue[0].iStart + ReadyQueue[0].iBurst;
    ReadyQueue[0].iWaiting = ReadyQueue[0].iResponse;
    ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;

    int curTime = 0;
    while (iTerminated < iNumberOfProcess) {
        while (iRemain > 0) {
            if (Input[0].iArrival <= ReadyQueue[0].iFinish) {
                if (startmap[ReadyQueue[0].iPID] == -1) {
                    startmap[ReadyQueue[0].iPID] = curTime;
                }
                pushProcess(&iGantt, Gantt, ReadyQueue[0]);
                Gantt[iGantt - 1].iBurst = Input[0].iArrival - curTime;
                curTime = Input[0].iArrival;
                Gantt[iGantt - 1].iFinish = curTime;
                ReadyQueue[0].iBurst = ReadyQueue[0].iBurst - Gantt[iGantt - 1].iBurst;

                pushProcess(&iReady, ReadyQueue, Input[0]);
                removeProcess(&iRemain, 0, Input);
                quickSort(ReadyQueue, 0, iReady - 1, SORT_BY_BURST);
                ReadyQueue[0].iFinish = curTime + ReadyQueue[0].iBurst;
            }
            else break;
        }

        if (iReady > 0) {
            ReadyQueue[0].iStart = startmap[ReadyQueue[0].iPID];
            ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
            ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;
            ReadyQueue[0].iWaiting = ReadyQueue[0].iTaT - burstmap[ReadyQueue[0].iPID];
            curTime = ReadyQueue[0].iFinish;
            pushProcess(&iTerminated, TerminatedArray, ReadyQueue[0]);
            pushProcess(&iGantt, Gantt, ReadyQueue[0]);
            removeProcess(&iReady, 0, ReadyQueue);
            if (startmap[ReadyQueue[0].iPID] == -1)
                startmap[ReadyQueue[0].iPID] = curTime;
            ReadyQueue[0].iFinish = curTime + ReadyQueue[0].iBurst;
        }
    }

    int pos = 0;
    for (int i = 1; i < iGantt; i++) {
        if (Gantt[pos].iPID == Gantt[i].iPID) {
            Gantt[pos].iBurst = Gantt[pos].iBurst + Gantt[i].iBurst;
            Gantt[pos].iFinish = Gantt[i].iFinish;
        }
        else {
            pos++;
            Gantt[pos] = Gantt[i];
        }
    }

    iGantt = ++pos;
    printf("\n===== SRTF Scheduling =====\n");
    exportGanttChart(iGantt, Gantt);
    quickSort(TerminatedArray, 0, iTerminated - 1, SORT_BY_PID);
    printProcess(iTerminated, TerminatedArray);
    calculateAWT(iTerminated, TerminatedArray);
    calculateATaT(iTerminated, TerminatedArray);
    printf("\n");

    return 0;
}
