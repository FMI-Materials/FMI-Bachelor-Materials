#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
struct thread_params{
    int line;
    int column;
};
int nrlin1, nrcol1, nrlin2, nrcol2;
int **First, **Second, **Result;
void* thread_routine(void* args){
    struct thread_params* index =  (struct thread_params*) args;
    int line = index->line;
    int column = index->column;
    free(index);
    int *result = (int*)malloc(sizeof(int));
    for(int k = 0;k < nrcol1; ++k)
        (*result) += First[line][k] * Second[k][column];
    return result;
}

int main(int argc, char* argv[]){
    printf("First matrix:\n");
    printf("Number of lines:\n");
    scanf("%d", &nrlin1);
    printf("Number of columns:\n");
    scanf("%d", &nrcol1);

    First = (int**) malloc(sizeof(int*) * nrlin1);
    for(int i = 0; i < nrlin1; ++i)
        First[i] = (int*) malloc(sizeof(int)*nrcol1);
    
    printf("Elements of the first matrix:\n");
    for(int i = 0; i < nrlin1; ++i)
        for(int j = 0; j < nrcol1; ++j)
            scanf("%d", &First[i][j]);

    printf("First matrix:\n");
    for(int i = 0; i < nrlin1; ++i){
        for(int j = 0; j < nrcol1; ++j)
            printf("%d ", First[i][j]);
        printf("\n");
    }

    printf("\nSecond matrix:\n");
    printf("Number of lines:\n");
    scanf("%d", &nrlin2);
    printf("Number of columns:\n");
    scanf("%d", &nrcol2);

    printf("Elements of the second matrix:\n");
    Second = (int**) malloc(sizeof(int*) * nrlin2);
    for(int i = 0; i < nrlin2; ++i)
        Second[i] = (int*) malloc(sizeof(int)*nrcol2);
    
    for(int i = 0; i < nrlin2; ++i)
        for(int j = 0; j < nrcol2; ++j)
            scanf("%d", &Second[i][j]);

    printf("Second matrix:\n");
    for(int i = 0; i < nrlin2; ++i){
        for(int j = 0; j < nrcol2; ++j)
            printf("%d ", Second[i][j]);
        printf("\n");
    }

    if(nrcol1 != nrlin2){
        perror("Impossibile\n");
        return errno;
    }
    else{
        pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * nrlin1 * nrcol2);
        int number_threads = 0;
        Result = (int**) malloc(sizeof(int) * nrlin1);
        for(int i = 0; i < nrlin1; ++i)
            Result[i] = (int*) malloc(sizeof(int)*nrcol2);

        for(int i = 0;i < nrlin1; ++i)
            for(int j = 0; j < nrcol2; ++j){
                struct thread_params *index = (struct thread_params*) malloc(sizeof(struct thread_params));
                index->line = i;
                index->column = j;      

                if(pthread_create(&threads[number_threads++], NULL,thread_routine, index)){
                    perror("Error at pthread_create");
                    return errno;
                }
                
            }

        number_threads = 0;
        for(int i = 0;i < nrlin1; ++i)
            for(int j = 0; j < nrcol2; ++j){
                void *retval;
                
                if(pthread_join(threads[number_threads++], &retval)){
                    perror("Error at pthread_create");
                    return errno;
                }
                int* ret = (int*) retval;
                Result[i][j] = *ret;
                free(ret);
            }
        
        printf("Result matrix:\n");
        for(int i = 0; i < nrlin1; ++i){
            for(int j = 0; j < nrcol2; ++j)
                printf("%d ", Result[i][j]);
            printf("\n");
        }
        for(int i = 0; i < nrlin1; ++i)
            free(Result[i]);
        free(Result);
        free(threads);
    }
    for(int i = 0;i < nrlin1; ++i)
        free(First[i]);
    free(First);

    for(int i = 0; i < nrlin2; ++i)
        free(Second[i]);
    free(Second);

    
    return 0;
}