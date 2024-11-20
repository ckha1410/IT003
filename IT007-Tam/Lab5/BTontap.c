#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
int x1, x2, x3, x4, x5, x6;
int w = 0, v = 0, y = 0, z = 0, ans = 0;
sem_t semCD, semE, semG;

void* thread_a(void* mess) {
    w = x1*x2;
    printf("w = x1*x2 = %d (a)\n", w);
    sem_post(&semE);
}

void* thread_b(void* mess) {
    v = x3*x4;
    printf("v = x3*x4 = %d (b)\n", v);
    sem_post(&semCD);
    sem_post(&semCD);
}

void* thread_c(void* mess) {
    sem_wait(&semCD);
    y = v*x5;
    printf("y = v*x5 = %d (c)\n", y);
    sem_post(&semE);
}

void* thread_d(void* mess) {
    sem_wait(&semCD);
    z = v*x6;
    printf("z = v*x6 = %d (d)\n", z);
}

void* thread_e(void* mess) {
    sem_wait(&semE);
    sem_wait(&semE);
    y = w*y;
    printf("y = w*y = %d (e)\n", y);
    sem_post(&semG);
}

void* thread_f(void* mess) {
    z = w*z;
    printf("z = w*z = %d (f)\n", z);
    sem_post(&semG);
}

void* thread_g(void* mess) {
    sem_wait(&semG);
    sem_wait(&semG);
    ans = y + z;
    printf("ans = y + z = %d (g)\n", ans);
}

int main() {
    pthread_t pA, pB, pC, pD, pE, pF, pG;
    scanf("%d %d %d %d %d %d", &x1, &x2, &x3, &x4, &x5, &x6);
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semCD, 0, 0);
    sem_init(&semE, 0, 0);
    sem_init(&semG, 0, 0);

    pthread_create(&pA, NULL, thread_a, NULL);
    pthread_create(&pB, NULL, thread_b, NULL);
    pthread_create(&pC, NULL, thread_c, NULL);
    pthread_create(&pD, NULL, thread_d, NULL);
    pthread_create(&pE, NULL, thread_e, NULL);
    pthread_create(&pF, NULL, thread_f, NULL);
    pthread_create(&pG, NULL, thread_g, NULL);

    sleep(5);
    sem_destroy(&semCD);
    sem_destroy(&semE);
    sem_destroy(&semG);
    pthread_mutex_destroy(&mutex);
    return 0;
}
