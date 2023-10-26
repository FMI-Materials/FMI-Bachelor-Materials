#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Problema 1
/// Creati o variabila de tip int si un pointer, modificati valoarea variabilei folosind pointer-ul
void p1(){
    int x = 13;
    int *a = &x;
    *a = 15;
    printf("%d", x);
}

/// Problema 2
/// Creati un vector de o lungime citita
void p2(){
    int l;
    scanf("%d", &l);
    int *a = (int*)malloc(l * sizeof (int));
    for(int i=0;i<l;i++)
        a[i] = i+1;
    for(int i=0;i<l;i++)
        printf("%d ", a[i]);
    free(a);
}

/// Problema 3
/// Creati o matrice de 10x10 folosind pointeri
void p3(){
    int **m = (int**) malloc(5 * sizeof (int*));
    int i, j;
    for(i=0;i<5;i++)
        m[i] = malloc(5 * sizeof (int));
    m[1][2] = 4;
    for(i=0;i<5;++i) {
        for (j = 0; j < 5; ++j)
            printf("%d ", m[i][j]);
        printf("\n");
    }
    for(i=0;i<5;++i)
        free(m[i]);
    free(m);
}

/// Problema 4 - siruri de caractere
/// Cititi un text si un cuvant. Numarati de cate ori apare acel cuvant in text
void p4(){
    unsigned long text_size = 255, word_size = 255;
    char *text = (char*) malloc(sizeof (char )*text_size);
    char *word = (char*) malloc(sizeof (char )*word_size);
    getline(&text, &text_size, stdin);
    getline(&word, &word_size, stdin);
    /// abc\0
    /// a\0
    word[strlen(word)-1] = '\0';
    text[strlen(text)-1] = '\0';
    int count = 0;
    /// ana are mere
    /// NULL
    char *buffer = strtok(text, " ");
    while (buffer!=NULL){
        if(strcmp(buffer, word)==0)
            count++;
        buffer = strtok(NULL, " ");
    }
    printf("Cuvantul apare de %d ori\n", count);
    free(text);
    free(word);
}

int main() {
    p4();
    return 0;
}