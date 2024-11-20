#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int x = 0;
void* processA(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20) x = 0;
        printf("Process A: x = %d\n", x);
        usleep(100000);
    }
}
void* processB(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20) x = 0;
        printf("Process B: x = %d\n", x);
        usleep(100000);
    }
}
int main() {
    pthread_t pA, pB;
    pthread_create(&pA, NULL, processA, NULL);
    pthread_create(&pB, NULL, processB, NULL);
    while(1){}
    return 0;
}


