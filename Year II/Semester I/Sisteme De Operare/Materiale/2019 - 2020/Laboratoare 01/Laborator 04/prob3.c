#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void collaz(int n)
{
	printf("%d: ", n);
	while (n != 1)
	{
		printf("%d ", n);
		if (n % 2 == 0)
			n = n / 2;
		else
			n = 3 * n + 1;
	}
	printf("%d \n", n);
}


int main(int argc, char const* argv[])
{
	if (argc == 0)
	{
		printf("Numar insuficent de argumente.\n");
		return -1;
	}
	printf("Starting Parent %d\n", getpid());
	for (int i = 1; i <= argc; ++i)
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			return errno;
		}
		else
			if (pid == 0)
			{
				int n = atoi(argv[i]);
				collaz(n);
				printf("Done Parent %d Me %d\n", getppid(), getpid());
				exit(1);
			}
	}
	for (int i = 1; i <= argc; ++i)
		wait();
	printf("Done Parent %d Me %d\n", getppid(), getpid());
	return 0;
}