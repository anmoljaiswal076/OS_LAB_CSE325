#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int commonVariable = 2;
void *countgold(void *param) {
    pthread_mutex_lock(&m);
    if(param){
      commonVariable = commonVariable + 1;
      printf("Common-Variable after incrementing - %d\n", commonVariable);
    }else{
      commonVariable = commonVariable - 1;
      printf("Common-Variable after decrementing - %d\n", commonVariable);
    }
    pthread_mutex_unlock(&m);
    return NULL;
}
int main(int argc, char* argv[]) {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, countgold,(void *)1);
    pthread_create(&tid2, NULL, countgold,(void *)0);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("The Final Common-Variable is - %d\n", commonVariable);
    return 0;
}
