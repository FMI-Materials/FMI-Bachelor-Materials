#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#define NR_THREADS 1000
#define MAX_INCREMENT 100

int count = 0;

void *tfun(void *v){

    for (int i = 0; i < MAX_INCREMENT; i++){
        count++;
    }
    return NULL;
}

int main(){
    pthread_t thr[NR_THREADS];

    for (int i = 0; i < NR_THREADS; i++){
        if (pthread_create(&thr[i], NULL, tfun, NULL)){
            perror(NULL);
            return errno;
        }
    }

    for (int i = 0; i < NR_THREADS; i++){
        if (pthread_join(thr[i], NULL)){
            perror(NULL);
            return errno;
        }
    }

    printf("Count este %d\n", count);

    return 0;
}