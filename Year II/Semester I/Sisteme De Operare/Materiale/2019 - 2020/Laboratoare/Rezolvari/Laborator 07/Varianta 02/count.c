#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
 
int available_resources = 5;
pthread_mutex_t mtx;
 
int decrease_count(int count)
{
    pthread_mutex_lock(&mtx);
    if (available_resources < count)
        {
            pthread_mutex_unlock(&mtx);
            return -1;
        }
    else
        {
        available_resources -= count;
        printf("Got: %d , remaining: %d \n",count, available_resources);
        }
    pthread_mutex_unlock(&mtx);
    return 1;
}
int increase_count(int count)
{   pthread_mutex_lock(&mtx);
    available_resources += count;
    printf("Released: %d , remaining: %d \n",count, available_resources);
    pthread_mutex_unlock(&mtx);
    return 0;
}
void thread_init(void *arg)
{  
    int cnt = (int) arg;
    if(decrease_count(cnt) == 1);
        increase_count(cnt);
    return NULL;   
   
}
int main()
{
   
    int count;
    pthread_t thr[6];
    for (int i=0; i<6; i++)
    {
        count = rand() % 5;
        pthread_create(&thr[i], NULL, thread_init, count);
    }
 
    for (int i=0; i <6; i++)
    {
        pthread_join(thr[i], NULL);
    }
    return 0;
}
