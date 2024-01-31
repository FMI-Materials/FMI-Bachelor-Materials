#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
void collatz(int argument){
    printf("%d ", argument);
    while(argument > 1){
        if(argument & 1){
            argument = 3 * argument + 1;
        } else{
            argument = argument / 2;
        }
        printf("%d ", argument);
    }
    printf("\n");
}
int main(){
    pid_t pid = fork();
    if(pid < 0){
        perror("Didnt't Fork\n");
        return errno;
    } else if(pid == 0){
        printf("From child, parent id = %d, child id = %d\n", getppid(), getpid());
        int argument;
        printf("Give argument:\n");
        scanf("%d", &argument);
        collatz(argument);

    } else {
        wait(NULL);
        printf("Child %d finished\n", pid);
        printf("From parent, parent id = %d, child id = %d\n", getpid(), pid);
        
    }
    return 0;
}