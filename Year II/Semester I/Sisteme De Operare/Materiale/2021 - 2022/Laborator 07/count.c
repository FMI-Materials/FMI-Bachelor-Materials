#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#define MAX_RESOURCES 10

int resources = MAX_RESOURCES;

pthread_mutex_t mutex;
pthread_t *threads;

int decrease_count(int count){
    pthread_mutex_lock(&mutex);

    if(resources >= count){
        resources = resources - count;
        printf("Got      : %d, Remaining Resources: %d\n", count, resources);
        pthread_mutex_unlock(&mutex);
    }
    else{
        printf("Not enough resources. Got : %d, Remaining Resources: %d\n", count, resources);
        pthread_mutex_unlock(&mutex);
        return -1;
    }

    return 0;
}

int increase_count(int count){
    pthread_mutex_lock(&mutex);
    resources += count;
    printf("Released : %d, Remaining Resources: %d\n", count, resources);
    pthread_mutex_unlock(&mutex);
    return 0;
}

void* thread_routine(void* arg){
    int* argument = (int*) arg;
    int count = *argument;
    if(!decrease_count(count)){
        //sleep(1e-10); -- daca pun un sleep aici, se executa mai multe threaduri odata
        // altfel, o sa se execute pe rand
        // timpul dintre alocarea de resurse si eliberarea de resurse e aproape inexistent, de aceea nu lasa alte thread uri
        // sa se execute
        increase_count(count);
    }
    free(argument);
    return NULL;
}

int main(){
    threads = (pthread_t*) malloc(MAX_RESOURCES * sizeof(pthread_t));

    if(pthread_mutex_init(&mutex, NULL)){
        perror("Error at pthread_mutex_init\n");
        return errno;
    }

    for(int i = 0; i < 10; ++i){
        int* argument;
        argument = (int*) malloc(sizeof(int));
        *argument = i;
        if(pthread_create(&threads[i], NULL, thread_routine, argument)){
            perror("Error at pthread_create\n");
            return errno;
        }
    }

    for(int i = 0; i < 10; ++i){
        if(pthread_join(threads[i], NULL)){
            perror("Error at pthread_join\n");
            return errno;
        }
        
    }
    if(pthread_mutex_destroy(&mutex)){
        perror("Error at pthread_mutex_destroy\n");
        return errno;
    }
    free(threads);
    return 0;


}


