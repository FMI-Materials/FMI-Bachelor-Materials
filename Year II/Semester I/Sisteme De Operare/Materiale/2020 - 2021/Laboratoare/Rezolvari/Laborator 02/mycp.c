#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int openFromFile(char* fileName){
    int ff = open(fileName, O_RDONLY, S_IRWXU);
    if(ff==-1){
        printf("Cannot open file! File may not exist, please check!\n");
        return -1;
    }
    return ff;
}

int openToFile(char* fileName){
    struct stat sb;
    stat(fileName, &sb);
    if(errno==0){
        printf("File already exists, rewrite? (y/n): ");
        char action;
        scanf("%c", &action);
        if(action!='y' && action!='Y')
            return -1;
    }
    int tf = open(fileName, O_CREAT | O_WRONLY, S_IRWXU);
    if(tf==-1) {
        printf("Cannot open file, aborting!\n");
        printf("Error no: %d\n", errno);
        return -1;
    }
    return tf;
}

int copyFile(int from, int to, int fileSize){
    const int DMAX = 1024;
    char* content = malloc(sizeof(char) * DMAX);
    int readResult, writeResult;
    while((readResult = read(from, content, DMAX))>0){
        int written = 0;
        printf("%s", content);
        while((writeResult = write(to, content+written, DMAX-written))>0)
            written += writeResult;
        if(writeResult==-1){
            printf("\nCannot write content, aborting!\n");
            printf("Error no: %d", errno);
            return errno;
        }
    }
    if(readResult==-1){
        printf("Error writing to file\n");
        printf("Error no: %d\n", errno);
        return -1;
    }
    return 0;
}

int main(int argc, char** argv){
    if(argc!=3){
        printf("Wrong format, please use: ./mycp <from> <to>\n");
        return 0;
    }
    char* fromFile = argv[1],* toFile = argv[2];
    int ff = openFromFile(fromFile);
    if(ff==-1)
        return 0;
    int tf = openToFile(toFile);
    if(tf==-1)
        return 0;
    struct stat sb;
    stat(fromFile, &sb);
    int fileSize = sb.st_size;
    if(copyFile(ff, tf, fileSize)==-1)
        return 0;
    close(ff);
    close(tf);
    return 0;
}
