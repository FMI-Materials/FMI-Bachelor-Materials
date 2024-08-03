#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#define NR_THREADS 10
#define MAX_INCREMENT 1
#define USE_MUTEX 0

int count = 0;

pthread_mutex_t mtx;

void *tfun(void *v){

    for (int i = 0; i < MAX_INCREMENT; i++){
        #if USE_MUTEX
        pthread_mutex_lock(&mtx);
        #endif
        count++; //critical section
        #if USE_MUTEX
        pthread_mutex_unlock(&mtx);
        #endif
    }
    return NULL;
}

int main(){
    pthread_t thr[NR_THREADS];
    #if USE_MUTEX
    if (pthread_mutex_init(&mtx, NULL))
    {
        perror(NULL);
        return errno;
    }
    #endif

    for (int i = 0; i < NR_THREADS; i++)
    {
        if (pthread_create(&thr[i], NULL, tfun, NULL))
        {
            perror(NULL);
            return errno;
        }
    }

    for (int i = 0; i < NR_THREADS; i++)
    {
        if (pthread_join(thr[i], NULL))
        {
            perror(NULL);
            return errno;
        }
    }


    printf("Count este %d\n", count);

    #if USE_MUTEX
    pthread_mutex_destroy(&mtx);
    #endif

    return 0;
}