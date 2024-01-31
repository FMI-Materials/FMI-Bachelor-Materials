#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mtx;
sem_t sem;
int nr;
int n = 5;
void bariera()
{
	pthread_mutex_lock(&mtx);
	nr++;


	if(nr < n)
	{	
		pthread_mutex_unlock(&mtx);
		sem_wait(&sem);
	}
	else			
	{
		pthread_mutex_unlock(&mtx);

		for(int i=0; i<n-1;i++)
			sem_post(&sem);
	}

	return;	

}

void thread_init(void *arg)
{
	int id = (int) arg;
	printf("Threadul cu id-ul %d a ajuns la bariera\n",id);
	bariera();
	printf("Threadul cu id-ul %d a trecut de bariera!!\n",id);
}
int main()
{
	

	pthread_t thr[6];
	sem_init(&sem, 0, 0);
	for (int i=0; i<5; i++)
	{
		pthread_create(&thr[i], NULL, thread_init, i);
	}

	for (int i=0; i <5; i++)
	{
		pthread_join(thr[i], NULL);
	}

	return 0;
}