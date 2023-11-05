#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * main - function that prints the parent PID
 * Return: nothing cos the code was successful
 */
int main(void)
{
	pid_t myppid = getppid();

	printf("%i\n", myppid);
	return (0);
}
