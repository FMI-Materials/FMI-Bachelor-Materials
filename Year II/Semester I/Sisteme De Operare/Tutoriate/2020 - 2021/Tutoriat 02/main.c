#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

/**
 * Functii de sistem
 *  - Folosite pentru a accesa servicii de sistem
 *  - Manual functii sistem: man 2 <syscall>
 *  Tipuri de functii de sistem:
 *   - Process control
 *   - File management:
 *    - int open(const char ∗path, int flags , ...);
 *    - ssize_t read(int d, void ∗buf, size t nbytes);
 *    - ssize_t write(int fildes, const void *buf, size_t nbyte); -> filedes = descrierea fisierului curent
 *    - int stat(const char ∗path, struct stat ∗sb);
 *   - Device management
 *   - Information maintenance
 *   - Communications
 *   - Protection
 */


/// 1. Scrieti un program ce sa afiseze pe ecran 'sisteme de operare' folosind functii de sistem
/// ssize_t write(int fildes, const void *buf, size_t nbyte);
/*int main(){
    write(1, "sisteme de operare", 18);
    return 0;
}*/


/// 2. Scrieti un program care sa primeasca la intrar un fisier sursa si sa afiseze continutul sau
/// Ex: cat2 hello -> 'Hello world'

int openFile(char* fileName){
    int ff = open(fileName, O_RDONLY, S_IRWXU);
    if(ff==-1){
        printf("Cannot open file! File may not exist, please check!\n");
        return -1;
    }
    return ff;
}

/*int main(int argc, char** argv){
    if(argc!=2){
        printf("Wrong format, please use: ./cat2 <source>\n");
        return 0;
    }
    char* fromFile = argv[1];
    int ff = openFile(fromFile);
    if(ff==-1)
        return 0;
    const int DMAX = 1024;
    char* content = malloc(sizeof(char) * DMAX);
    int readResult;
    while((readResult = read(ff, content, DMAX))>0)
        write(1, content, strlen(content));
    if(readResult==-1){
        printf("Error no: %d\n", errno);
        return -1;
    }
    close(ff);
    return 1;
}*/

/// 3. Modificati programul creat astfel incat sa putem concatena (optional) un text dat la contiuntul fisierului
/// Ex: cat2 hello world -> 'Hello world world'

int main(int argc, char** argv){
    if(argc!=2 && argc!=3){
        printf("Wrong format, please use: ./cat2 <source> [<text>]\n");
        return 0;
    }
    char* fromFile = argv[1];
    int ff = openFile(fromFile);
    if(ff==-1)
        return 0;
    const int DMAX = 1024;
    char* content = malloc(sizeof(char) * DMAX);
    int readResult;
    while((readResult = read(ff, content, DMAX))>0)
        write(1, content, strlen(content));
    write(1, argv[2], strlen(argv[2]));
    if(readResult==-1){
        printf("Error no: %d\n", errno);
        return -1;
    }
    close(ff);
    return 1;
}
