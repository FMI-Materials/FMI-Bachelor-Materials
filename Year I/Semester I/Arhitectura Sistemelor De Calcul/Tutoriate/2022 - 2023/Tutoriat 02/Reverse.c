#include <stdio.h>
#include <string.h>
char s[50], rev[50];
char *ptr = s;                  // C trickery to get no warning

int main(){
    size_t buff_size = 50;      // C trickery to get no warning
    int len = getline(&ptr, &buff_size, stdin);     // functia returneaza cate caractere au fost citite cu succes

    // in getline dau ca parametri  1.  un pointer catre sirul de caractere
    //                              2.  un pointer catre variabila care indica numarul maxim de caractere citite
    //                              3.  stdin (se citeste de la consola)
    /*  Alternativ ar fi mers si:
     *
     *  gets(s);
     *  int len = strlen(s);
     *  
     *  In codul assembly am folosit implementarea cu get(s) deoarece este mai usoara!
     * */

    rev[len] = '\0';
    for(int i = len - 1, j = 0; i >= 0; --i, ++j)   //  daca nu intelegeti dati-mi mesaj
        rev[j] = s[i];

    puts(rev);                  //  afisez string-ul
    return 0;
}
