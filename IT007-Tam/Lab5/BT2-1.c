#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAX 100000
int cnt = 0;
int a[MAX];
void* process1(void* mess) {
    while(1) {
        if (cnt < MAX) {
            a[cnt++] = rand() % 100;
            printf("\n[PUSH] Numer of elements in array: %2d", cnt);
        }
        sleep(1);
    }
}
void* process2(void* mess) {
    while(1) {
        if (cnt == 0)
            printf("\n[POP] Nothing in array");
        else {
            cnt--;
            printf("\n[POP] Numer of elements in array: %2d", cnt);
        }
        sleep(1);
    }
}
int main() {
    pthread_t p1, p2;
    pthread_create(&p1, NULL, &process1, NULL);
    pthread_create(&p2, NULL, &process2, NULL);
    while(1){}
    return 0;
}
