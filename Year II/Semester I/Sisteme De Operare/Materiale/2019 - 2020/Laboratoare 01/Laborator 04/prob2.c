#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char* argv[]) {

	pid_t pid = fork();
	if(pid < 0)
		return errno;
	else 
	if (pid == 0) {
		if(argc <= 1) {
			printf("Nu exista argumente suficiente.\n");
			perror(NULL); 
		}

		int numarul = atoi(argv[1]);
		printf("%d: ", numarul);
		while(1) {
			printf("%d ", numarul);
			if(numarul == 1)
				break;
			if(numarul % 2 == 0)
				numarul = numarul / 2;
			else
				numarul = 3*numarul + 1;
		}
		printf("\n");
	}
	else {
		wait();
		printf("Child %d finished\n",  getpid());
	}
	return 0;
}