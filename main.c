#include "main.h"
/**
* main - runs the main function
* @argc: first arguement.
* @argv: pointer arguenebt
* Return: (0).
*/
int main(int argc, char *argv[])
{
	(void)argv;
	if (argc == 1)
	{
		return (run_shell("$ ", argv[0]));
	}
	else
	{
		perror("Usage: ./hsh");
		exit(EXIT_FAILURE);
	}
	return (0);
}
