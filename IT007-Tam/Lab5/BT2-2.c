#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAX 100
int a[MAX];

int cnt = 0;
sem_t sem_add;
sem_t sem_remove;
pthread_mutex_t mutex;

void* process1(void* mess) {
    while(1) {
        sem_wait(&sem_add);
        pthread_mutex_lock(&mutex);
        a[cnt++] = rand() % 100;
        printf("\n[PUSH] Numer of elements in array: %2d", cnt);
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_remove);
        sleep(1);
    }
}

void* process2(void* mess) {
    while (1) {
        sem_wait(&sem_remove);
        pthread_mutex_lock(&mutex);
        if (cnt == 0)
            printf("\n[POP] Nothing in array");
        else {
            cnt--;
            printf("\n[POP] Numer of elements in array: %2d", cnt);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_add);
        sleep(1);
    }
}

int main() {
    sem_init(&sem_add, 0, MAX);
    sem_init(&sem_remove, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t p1, p2;
    pthread_create(&p1, NULL, process1, NULL);
    pthread_create(&p2, NULL, process2, NULL);

    while(1){}

    sem_destroy(&sem_add);
    sem_destroy(&sem_remove);
    pthread_mutex_destroy(&mutex);
    return 0;
}
