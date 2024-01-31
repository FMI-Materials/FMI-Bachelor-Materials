#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if(argc<2) return -1;
    int n = atoi(argv[1]);
    pid_t pid = fork();
    if(pid<0)
        return errno;
    else if(pid!=0 && n>1){
        n = (n%2) ? 3*n+1 : n/2;
        char strn[10];
        sprintf(strn, "%d", n); 
        char *argv2[] = {"collatz", strn};
        execve("/Users/dariusbuhai/Desktop/FMI-Unibuc/Anul II/Semestrul 1/SO/Lab5/collatz", argv2 , NULL);
    }else if(pid==0){
        wait(NULL);
        printf("%d ", n);
        if(n==1)
            printf("\nChild %d finished\n", getpid());
    }
    return 0;
}
