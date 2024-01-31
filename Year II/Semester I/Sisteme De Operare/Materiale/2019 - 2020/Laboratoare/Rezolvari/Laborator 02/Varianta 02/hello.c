#include <unistd.h>

int main()
{
	const char *message = "Hello World! \n";
	write(1 , message, strlen(message));
	return 0;
}