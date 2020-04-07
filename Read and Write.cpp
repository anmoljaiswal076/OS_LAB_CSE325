#define _GNU_SOURCE
#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void *reader(void *);
void *writer(void *);
int readcount=0,writecount=0,temp=5;
sem_t x,y,z,rsem,wsem;
pthread_t r[5],w[3];
void *reader(void *i){
	printf("\n\nReader #%p is reading\n",i);
        sem_wait(&z);
        sem_wait(&rsem);
        sem_wait(&x);
        readcount++;
        if(readcount==1)
            sem_wait(&wsem);
        sem_post(&x);
        sem_post(&rsem);
        sem_post(&z);
	printf("\nupdated value : %d\n",temp);
	sem_wait(&x);
        readcount--;
        if(readcount==0)
            sem_post(&wsem);
        sem_post(&x);
        return NULL;
}
void *writer(void *i){
	printf("\n\nWriter #%p is writing\n",i);
	sem_wait(&y);
        writecount++;
        if(writecount==1)
        sem_wait(&rsem);
        sem_post(&y);
        sem_wait(&wsem);
        temp=temp+5;
        sem_post(&wsem);
        sem_wait(&y);
        writecount--;
        if(writecount==0)
        sem_post(&rsem);
        sem_post(&y);
        return NULL;
}
int main(int argc, char* argv[]){
        sem_init(&x,0,1);
        sem_init(&wsem,0,1);
        sem_init(&y,0,1);
        sem_init(&z,0,1);
        sem_init(&rsem,0,1);
        pthread_create(&r[0],NULL,(void *)reader,(void *)1);
        pthread_create(&w[0],NULL,(void *)writer,(void *)1);
        pthread_create(&r[1],NULL,(void *)reader,(void *)2);
        pthread_create(&w[1],NULL,(void *)writer,(void *)2);
        pthread_create(&r[2],NULL,(void *)reader,(void *)3);
        pthread_create(&r[3],NULL,(void *)reader,(void *)4);
        pthread_create(&w[2],NULL,(void *)writer,(void *)3);
        pthread_create(&r[4],NULL,(void *)reader,(void *)5);
        pthread_join(r[0],NULL);
        pthread_join(w[0],NULL);
        pthread_join(r[1],NULL);
        pthread_join(r[2],NULL);
        pthread_join(r[3],NULL);
        pthread_join(w[1],NULL);
        pthread_join(w[2],NULL);
        pthread_join(r[4],NULL);
        sem_destroy(&x);
        sem_destroy(&wsem);
        sem_destroy(&y);
        sem_destroy(&z);
        sem_destroy(&rsem);
        return(0);
}
