#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t sem1, sem2;
int sells = 0, products = 0;
void* processA(void* mess) {
    while(1) {
        sem_wait(&sem1);
        sells++;
        printf("sells = %d\n", sells);
        sem_post(&sem2);
        usleep(100000);
    }
}
void *processB(void* mess) {
    while(1) {
        sem_wait(&sem2);
        products++;
        printf("products = %d\n", products);
        sem_post(&sem1);
        usleep(150000);
    }
}
int main() {
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 36);
    pthread_t pA, pB;
    pthread_create(&pA, NULL, &processA, NULL);
    pthread_create(&pB, NULL, &processB, NULL);
    while(1){}
    return 0;
}


