#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count_occurrences(const char* text, const char* word){
    int nr = 0;
    char *p = text;
    char sep[25] = ".?/<>, !';:-_";
    int lungime = strlen(word);
    p = strstr(p, word);
    while(p){
        if((p == text || strchr(sep,*(p-1))) && strlen(p) <= lungime || strchr(sep,*(p + lungime)))
        ++nr;
        if(strlen(p) >= lungime)
            p = p + lungime;
        p = strstr(p, word);
    }
    return nr;
    
}
char* replace(){
    char *text = malloc(256 * sizeof(char));
    char *word1 = malloc(25 * sizeof(char));
    char *word2 = malloc(25 * sizeof(char));
    char aux[256];
    scanf("%s\n%s\n", word1, word2);
    fgets(text, 256, stdin);
    char sep[25] = ".?/<>, !';:-_";
    int lungime1 = strlen(word1);
    int lungime2 = strlen(word2);
    int n = count_occurrences(text, word1); 
    int p1, p2 =-1;
    char *p = text;
    strcpy(aux,"");
    p = strstr(text, word1);
    while(n){
        if((p == text || strchr(sep,*(p-1))) && strlen(p) <= lungime1 || strchr(sep,*(p + lungime1))){
            p1 = p - text;

            if(p2 == -1){
            strncpy(aux,text,p1);
            strncat(aux,word2,lungime2);
            p2 = p1 + lungime1;
            }
            else{
                strncat(aux, text + p2,p1-p2);
                strncat(aux,word2,lungime2);
                p2 = p1 + lungime1;
            }
        
            --n;
        }
        if(strlen(p) >= lungime2)
            p = p + lungime2;
        p = strstr(p, word1);
    }

    free(word1);
    free(word2);
    strncat(aux, text + p2, strlen(text) - p2);
    strcpy(text, aux);
    return text;
    
}

int main(){
    
    printf("%s", replace());
    

    return 0;
}