#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void collatz(int x){
    printf("%d ", x);
    if(x==1) return;
    x = (x%2) ? 3*x+1 : x/2;
    collatz(x);
}

int main(int argc, char **argv){
    if(argc<2) return -1;
    printf("Starting parent %d\n", getppid());
    pid_t pids[argc];
    for(int i=0;i<argc;++i)
        if((pids[i]=fork())<0)
            return errno;
        else if(pids[i]==0){
            int n = atoi(argv[i+1]);
            printf("%d: ", n);
            collatz(n);
            printf("\n");
            exit(0);
        }
    for(int i=0;i<argc;++i){
        printf("Done Parent %d Me %d\n", getppid(), getpid());
        wait(NULL);
    }
    return 0;
}
