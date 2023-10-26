/*
 * Va recomand sa va scrieti codul assembly pe baza codului asta:
 * */

#include <stdio.h>

int M[100][100], M1[100][100], V[100], n, C, k, start, fin;

void matrix_mult(int m1[][100], int m2[][100], int mres[][100], const int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            V[j] = 0;
            for(int k = 0; k < n; ++k){
                V[j] += m1[i][k] * m2[k][j];
            }
        }
        for (int j = 0; j < n; ++j) {
            mres[i][j] = V[j];
        }
    }
}

void afisare(){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j)
            printf("%d ", M[i][j]);
        puts("");
    }
}

void citire(){
    int temp;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &V[i]);
    }
    for(int i = 0; i < n; ++i){
        while(V[i]--){
            scanf("%d", &temp);
            M1[i][temp] = M[i][temp] = 1;
        }
    }
}
int main(){
    scanf("%d", &C);
    if(C == 1) {
        citire();
        afisare();
    }
    else if(C == 2){
        citire();
        scanf("%d %d %d", &k, &start, &fin);
        for(int i = 0; i < k-1; ++i){
            matrix_mult(M, M1, M, n);
        }
        printf("%d\n", M[start][fin]);
    }
    else{
        ;
    }
    return 0;
}