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

int main(){
    printf("%d\n", count_occurrences("ana are mere pere si banane.", "ana"));
    return 0;
}