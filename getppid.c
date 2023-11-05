#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t myppid = getppid();

	printf("%i\n", myppid);
	return (0);
}
