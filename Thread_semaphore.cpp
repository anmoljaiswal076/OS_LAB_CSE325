#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
sem_t x,y,z;
pthread_t t[3];
void* functionA(void* lol){
  printf("Thread A trying to lock 0...\n");
  sem_wait(&x);
  printf("Thread A locked 0.\n");
  usleep(50*1000);
  printf("Thread A trying to lock 1...\n");
  sem_wait(&y);
  printf("Thread A locked 1.\n");
  sem_post(&x);
  sem_post(&y);
  return NULL;
}
void* functionB(void* lol){
  printf("Thread B trying to lock 2...\n");
  sem_wait(&y);
  printf("Thread B locked 2.\n");
  usleep(50*1000);
  printf("Thread B trying to lock 3...\n");
  sem_wait(&z);
  printf("Thread B locked 3.\n");
  sem_post(&y);
  sem_post(&z);
  return NULL;
}
void* functionC(void* lol){
  printf("Thread C trying to lock 3...\n");
  sem_wait(&z);
  printf("Thread C locked 3.\n");
  usleep(50*1000);
  printf("Thread C trying to lock 1...\n");
  sem_wait(&x);
  printf("Thread C locked 1.\n");
  sem_post(&z);
  sem_post(&x);
  return NULL;
}
int main(int argc, char* argv[]){
  sem_init(&x,0,1);
  sem_init(&y,0,1);
  sem_init(&z,0,1);
  pthread_create(&t[0],NULL,(void *)functionA,NULL);
  pthread_create(&t[1],NULL,(void *)functionB,NULL);
  pthread_create(&t[2],NULL,(void *)functionC,NULL);
  for (int i = 0 ; i < 3 ; i++) {
      pthread_join(t[i], NULL);
  }
  printf("This is seen,you are deadlock!");
  sem_destroy(&x);
  sem_destroy(&y);
  sem_destroy(&z);
}
