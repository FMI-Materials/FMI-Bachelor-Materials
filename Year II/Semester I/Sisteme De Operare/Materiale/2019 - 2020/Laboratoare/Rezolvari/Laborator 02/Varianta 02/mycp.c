#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int fd1, fd2;

	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1)
	{
		printf("Eroare la desciderea primului fisier, aflat la: %s \n", argv[1]);
		return -1;
	}

	fd2 = open(argv[2], O_WRONLY);
	if(fd2 == -1)
	{
		printf("Eroare la desciderea celui de al doilea fisier, aflat la: %s \n", argv[2]);
		return -1;
	}

	char* buff;
	buff = malloc(1024 * sizeof(char));

	while (read(fd1, buff, 1024 * sizeof(char)) == 1024)
	{
		size_t w = write(fd2, buff, 1024 * sizeof(char));
		if (w == -1)
		{
			printf("Eroare la scrierea in fisier.");
			return -1;
		}
	}	


	if (read(fd1, buff, 1024 * sizeof(char)) == -1)
	{
		printf("Eroare la citirea din primul fisier");
		return - 1;
	}
	
	size_t w =  write(fd2, buff, 1024 * sizeof(char));
	if(w == -1)
	{
		printf("Eroare la scrierea in fisier.(Ultima parte)");
		return -1;
	}

	close(fd1);
	close(fd2);
	
	return 0;
}