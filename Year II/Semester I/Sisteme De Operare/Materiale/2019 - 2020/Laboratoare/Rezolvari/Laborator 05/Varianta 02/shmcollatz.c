#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>


int collatz(int* buffer, int n) 
{
	buffer[0] = n;
	int k = 1;
	while (n != 1) 
	{
		if (n % 2 == 0) 
			n = n / 2;
		else 
			n = 3 * n + 1;
		buffer[k] = n;
		k++;
	}
	return 0;
}




int main(int argc, char* argv[])
{
	char shm_name[] = "/collatz";
	int shm_fd;

	shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	size_t shm_size = 2048 * argc;
	ftruncate(shm_fd, shm_size);
	int* addr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	printf("Starting parent %d\n", getpid());

	for (int i = 1; i < argc; i++) {
		pid_t pid = fork();
		int n = atoi(argv[i]);

		if (pid < 0) {
			printf("Fork failed");
			return errno;
		}
		else if (pid == 0) {
			printf("Done parent %d Me %d\n", getppid(), getpid());
			int* buffer = addr + (i - 1) * 2048 / sizeof(int);
			collatz(buffer, n);
			return 0;
		}
	}

	for (int i = 0; i < argc; i++) {
		wait(NULL);
	}

	for (int i = 1; i < argc; i++) {
		int*  buffer = addr + (i - 1) * 2048 / sizeof(int);
		int j = 0;
		printf("%d: ", buffer[j]);

		while (buffer[j] != 1) {
			printf("%d ", buffer[j]);
			j++;
		}
		printf("\n");

	}
	shm_unlink("/collatz");
	return 0;
}
