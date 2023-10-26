#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
 
int m1[50][50], m2[50][50], m3[50][50],n, m, p;
 
void *myThreadFun(void *vargp)
{
    int *a = (int*)vargp;
    int i = a[1];
    int j = a[2];
    m3[i][j] = 0;
    for (int k = 1; k <= n; k++)
       m3[i][j] += m1[i][k] * m2[k][j];
 
    return NULL;
}
 
void random_matrix(){
   
   srand(time(NULL));
   for(int i=1;i<=m;i++)
     for(int j=1;j<=n;j++)
      {
        m1[i][j] = rand() % 100;
      }  
 
   for(int i=1; i<=n;i++)
     for(int j=1; j<=p;j++)
      {
       m2[i][j] = rand() % 100;
      }      
 
}
int main()
{
    n = 2;
    m = 3;
    p = 2;
    random_matrix();
    pthread_t thread_ids[100];
    int k=0;
    for (int i=1;i<=m;i++)
    for(int j=1;j<=p;j++)
        {
          pthread_t thread_id;
          thread_ids[k++] = thread_id;
   
          int *a = malloc(5 * sizeof(int) );
   
          a[1] = i;
          a[2] = j;
          pthread_create(&thread_id, NULL, myThreadFun, a);
        }
   
    for(int i=1; i<m*p;i++)
    {
      pthread_join(thread_ids[i], NULL);
 
    }
 
     for (int i=1;i<=m;i++)
    {
      for(int j=1;j<=p;j++)
          printf("%d ",m3[i][j]);
        
        printf("\n");  
    }
     
    exit(0);
}
