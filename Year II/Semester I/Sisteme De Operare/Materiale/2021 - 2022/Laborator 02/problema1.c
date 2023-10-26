#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, i, j;
    int **matrice;

    printf("introduceti nr de linii:\n");
    scanf("%d", &n);

    matrice = malloc(sizeof(int*) * n);
    
    for(i = 0; i < n; ++i)
        *(matrice + i) = malloc(sizeof(int) * n);

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", (*(matrice + i) + j));
    printf("\n\nMatrice:\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++)
            printf("%d ", *(*(matrice + i) + j));
        printf("\n");
    }
    printf("\n\n");
    if(n & 1){
        printf("Elementul de la intersectia diagonalelor: %d", *(*matrice + (n/2 + 1)) + (n/2 + 1));
        printf("\n\n");
    }
    printf("Elementele de pe diagonala principala:\n");
    for(i = 0; i < n; i++)
        printf("%d ", *(*(matrice + i) + i));
    printf("\nElementele de pe diagonala secundara:\n");
    for(i = 0; i < n; i++)
        printf("%d ", *(*(matrice + i) + n-i-1));

    for(i = 0; i < n; ++i)
        free(*(matrice + i));
    free(matrice);
    return 0;
}