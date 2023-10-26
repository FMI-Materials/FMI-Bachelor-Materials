#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 5

/// 2. Scrieti un program ce aduna 2 vectori intre ei in thread-uri separate

int mat1[SIZE][SIZE] = {
        {1, 3, 5, 7, 1},
        {1, 3, 5, 7, 1},
        {1, 3, 4, 7, 1},
        {1, 3, 5, 0, 1},
        {1, 3, 5, 7, 1},
};
int mat2[SIZE][SIZE] = {
        {10, 4, -10, 11, 1},
        {11, 4, -10, 11, 1},
        {10, 4, -10, 11, 1},
        {15, 4, -19, 11, 1},
        {10, 4, -10, 11, 1},
};
int result[SIZE][SIZE];

struct pos {
    int i, j;
};

void *sum(void *pos_void) {
    struct pos* index = (struct pos*)pos_void;
    result[index->i][index->j] = mat1[index->i][index->j] + mat2[index->i][index->j];
    return (void*) (index->i * SIZE + index->j);
}

int main() {
    pthread_t *threads = malloc(sizeof(pthread_t) * SIZE * SIZE);
    /// threads [0 ... 24]
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            struct pos *index = malloc(sizeof(struct pos));
            index->i = i;
            index->j = j;
            pthread_create(threads + (i*SIZE + j), NULL, sum, index);
        }
    }
    for (int i = 0; i < SIZE * SIZE ; ++i){
        void *void_index = malloc(sizeof (int));
        pthread_join(threads[i], void_index);
        int* index = (int*)void_index;
        printf("%d ", *index);
    }
    printf("\n");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j)
            printf("%d ", result[i][j]);
        printf("\n");
    }
    return 0;
}