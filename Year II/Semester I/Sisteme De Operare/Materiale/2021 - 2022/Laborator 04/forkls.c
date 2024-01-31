#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){

    pid_t pid = fork();
    if(pid < 0){
        perror("Didnt't Fork\n");
        return errno;
    } else if(pid == 0){
        printf("From child, parent id = %d, child id = %d\n", getppid(), getpid());
        const char* path = "/usr/bin/ls";
        char* argv[] = {"ls", NULL};
        execve(path, argv, NULL);
    } else {
        wait(NULL);
        printf("From parent, parent id = %d, child id = %d\n", getpid(), pid);
    }
	return 0;
}