#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {

	pid_t pid = fork();
	if (pid < 0)
		return errno;
	else 
	if (pid == 0) {
		char *argv[] = {"ls", NULL};
		execve("/bin/ls", argv, NULL);
		perror(NULL);
	}
	else {
		printf("My PID = %d Child PID = %d\n", getppid(), getpid());
		wait();
		printf("Child %d finished\n",  getpid());
	}
	return 0;
}