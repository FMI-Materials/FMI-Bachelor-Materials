#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

/**
 * Functii de sistem
 *  - Folosite pentru a accesa servicii de sistem
 *  - Manual functii sistem: man 2 <syscall>
 *  Tipuri de functii de sistem:
 *   - Process control
 *   - File management:
 *    - int open(const char ∗path, int flags , ...);
 *    - ssize_t read(int d, void ∗buf, size t nbytes);
 *    - ssize_t write(int fildes, const void *buf, size_t nbyte);
 *    - int stat(const char ∗path, struct stat ∗sb);
 *   - Device management
 *   - Information maintenance
 *   - Communications
 *   - Protection
 */


/// 1. Scrieti un program ce sa afiseze pe ecran 'sisteme de operare' folosind functii de sistem
/// ssize_t write(int fildes, const void *buf, size_t nbyte);
//int main(){
//    write(2, "sisteme de operare", 18);
//}


/// 2. Scrieti un program care sa primeasca la intrare un fisier sursa si sa afiseze continutul sau concatenat cu un text dat
/// Ex: cat2 hello again -> 'Hello world again'

// gcc main.c -o cat2
// ./cat2 hello again

int openFile(char* fileName){
    int ff = open(fileName, O_RDONLY);
    printf("%d", ff);
    if(ff==-1){
        printf("Cannot open file!\n");
        return -1;
    }
    return ff;
}

int main(int argc, char** argv){
    if(argc!=3){
        printf("Wrong format, please use: ./cat2 <source> <text>\n");
        return -1;
    }
    char* fromFile = argv[1];
    int ff = openFile(fromFile);
    if(ff==-1)
        return -1;
    /// Folosind functia stat
    struct stat* buf = malloc(sizeof (struct stat));
    stat(fromFile, buf);
    char* content = malloc(sizeof (char) * buf->st_size);
    int readResult = read(ff, content, buf->st_size);
    if(readResult>0)
        write(1, content, readResult);
    /// Citind constant cate 1024 bytes
    //    const int DMAX = 1024;
    //    char* content = malloc(sizeof(char) * DMAX);
    //    int readResult;
    //    while((readResult = read(ff, content, DMAX))>0)
    //        write(1, content, readResult);
    write(1, argv[2], strlen(argv[2]));
    if(readResult==-1){
        printf("Error no: %d\n", errno);
        return -1;
    }
    close(ff);
    return 0;
}